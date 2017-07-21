#include <functional>

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "CodeEditor.hpp"
#include "NipypeStupidExceptions.hpp"
#include "NipypeGenerator.hpp"
#include "Port.hpp"
#include "PortPair.hpp"

const QString NipypeStupidExceptions::s_thisLanguage("NiPype");

NipypeStupidExceptions::NipypeStupidExceptions() :
    Singleton()
{
}

QString NipypeStupidExceptions::exceptionNodetoCode(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& _parameters
        ) const
{
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    QString node = title.getName();
    if (!node.compare("utility.IdentityInterface"))
    {
        return codeForIdentityInterface(_item, _parameters);
    }
    else if (!node.compare("io.SelectFiles"))
    {
        return codeForSelectFiles(_item, _parameters);
    }
    else if (!node.compare("io.MySQLSink"))
    {
        return codeForMySQLSink(_item, _parameters);
    }
    else if (!node.compare("io.SQLiteSink"))
    {
        return codeForSQLiteSink(_item, _parameters);
    }
    return QString("");
}


QString NipypeStupidExceptions::codeForIdentityInterface(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& _parameters
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage).isEmpty()) return QString("");

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));

    code += QString("#%1\n").arg(title.getComment(s_thisLanguage));
    code += QString("%1 = pe.").arg(nodeName);

    QStringList iterFields = getMapNodeFields(_item);
    if(iterFields.length() == 0)
    {
        code += "Node";
    }
    else
    {
        code += "MapNode";
    }

    QStringList fieldNodes;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        if(argument.isInput() && argument.isOutput())
        {
            fieldNodes << argument.getArgument(s_thisLanguage);
        }
    }

    code += QString("(utility.IdentityInterface(fields=['%1").arg(fieldNodes.join("','"));
    code += QString("']), name = 'NodeName_%1'").arg(QString::number((quint64) _item->getNode(), 16));

    if(iterFields.length() == 0)
    {
        code += ")\n";
    }
    else
    {
        code += QString(", iterfield = ['%1'])\n").arg(iterFields.join("', '"));
    }

    QStringList keyValuePairs;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        QString filename = _item->getParameterName(argument.getName());

        //replace filename
        foreach (const QString parameter, _parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty() && argument.isInput())
        {
            if(!argument.isIterator())
            {
                code += QString("%1.inputs.%3 = %4\n").arg(nodeName, argument.getArgument(s_thisLanguage), filename);
            }
            else if(pair->getInputPort()->getConnections().length() == 0)
            {
                keyValuePairs << QString("('%1', %2)").arg(argument.getArgument(s_thisLanguage), filename);
            }
        }
    }

    if(keyValuePairs.length() != 0)
    {
        code += QString("%1.iterables = [%2]\n").arg(nodeName, keyValuePairs.join(", "));
    }

    code += "\n";
    return code;
}

QString NipypeStupidExceptions::codeForSelectFiles(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& _parameters
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage).isEmpty()) return QString("");

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));

    code += QString("#%1\n").arg(title.getComment(s_thisLanguage));
    code += QString("%1 = pe.").arg(nodeName);

    QStringList iterFields = getMapNodeFields(_item);
    if(iterFields.length() == 0)
    {
        code += "Node";
    }
    else
    {
        code += "MapNode";
    }

    QStringList templateDictionary;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        QString filename = _item->getParameterName(argument.getName());

        //replace filename
        foreach (const QString parameter, _parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }
        if(!filename.isEmpty() && argument.isInput() && argument.isOutput())
        {
            templateDictionary << "'" + argument.getArgument(s_thisLanguage) + "':" + filename;
        }
    }

    code += QString("(io.SelectFiles(templates={%1").arg(templateDictionary.join(","));
    code += QString("}), name = 'NodeName_%1'").arg(QString::number((quint64) _item->getNode(), 16));

    if(iterFields.length() == 0)
    {
        code += ")\n";
    }
    else
    {
        code += QString(", iterfield = ['%1'])\n").arg(iterFields.join("', '"));
    }

    QStringList keyValuePairs;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        QString filename = _item->getParameterName(argument.getName());

        //replace filename
        foreach (const QString parameter, _parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty() && argument.isInput() && !argument.isOutput())
        {
            if(!argument.isIterator())
            {
                code += QString("%1.inputs.%2 = %3\n").arg(nodeName, argument.getArgument(s_thisLanguage), filename);
            }
            else if(pair->getInputPort()->getConnections().length() == 0)
            {
                keyValuePairs << QString("('%1', %2)").arg(argument.getArgument(s_thisLanguage), filename);
            }
        }
    }

    if(keyValuePairs.length() != 0)
    {
        code += QString("%1.iterables = [%2]\n").arg(nodeName, keyValuePairs.join(", "));
    }

    code += "\n";
    return code;
}

QString NipypeStupidExceptions::codeForMySQLSink(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& _parameters
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage).isEmpty()) return QString("");

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));

    code += QString("#%1\n").arg(title.getComment(s_thisLanguage));
    code += QString("%1 = pe.").arg(nodeName);

    QStringList iterFields = getMapNodeFields(_item);
    if(iterFields.length() == 0)
    {
        code += "Node";
    }
    else
    {
        code += "MapNode";
    }

    QStringList fieldNodes;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        if(argument.isInput() && argument.isOutput())
        {
            fieldNodes << argument.getArgument(s_thisLanguage);
        }
    }

    code += QString("(io.MySQLSink(input_names=['%1").arg(title.getArgument(fieldNodes.join("','")));
    code += QString("']), name = 'NodeName_%1'").arg(QString::number((quint64) _item->getNode(), 16));

    if(iterFields.length() == 0)
    {
        code += ")\n";
    }
    else
    {
        code += QString(", iterfield = ['%1'])\n").arg(iterFields.join("', '"));
    }

    QStringList keyValuePairs;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        QString filename = _item->getParameterName(argument.getName());

        //replace filename
        foreach (const QString parameter, _parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty() && argument.isInput())
        {
            if(!argument.isIterator())
            {
                code += QString("%1.inputs.%3 = %4\n").arg(nodeName, argument.getArgument(s_thisLanguage), filename);
            }
            else if(pair->getInputPort()->getConnections().length() == 0)
            {
                keyValuePairs << QString("('%1', %2)").arg(argument.getArgument(s_thisLanguage), filename);
            }
        }
    }

    if(keyValuePairs.length() != 0)
    {
        code += QString("%1.iterables = [%2]\n").arg(nodeName, keyValuePairs.join(", "));
    }

    code += "\n";
    return code;
}

QString NipypeStupidExceptions::codeForSQLiteSink(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& _parameters
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage).isEmpty()) return QString("");

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));

    code += QString("#%1\n").arg(title.getComment(s_thisLanguage));
    code += QString("%1 = pe.").arg(nodeName);

    QStringList iterFields = getMapNodeFields(_item);
    if(iterFields.length() == 0)
    {
        code += "Node";
    }
    else
    {
        code += "MapNode";
    }

    QStringList fieldNodes;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        if(argument.isInput() && argument.isOutput())
        {
            fieldNodes << argument.getArgument(s_thisLanguage);
        }
    }

    code += QString("(io.SQLiteSink(input_names=['%1").arg(title.getArgument(fieldNodes.join("','")));
    code += QString("']), name = 'NodeName_%1'").arg(QString::number((quint64) _item->getNode(), 16));

    if(iterFields.length() == 0)
    {
        code += ")\n";
    }
    else
    {
        code += QString(", iterfield = ['%1'])\n").arg(iterFields.join("', '"));
    }

    QStringList keyValuePairs;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        Argument argument = pair->getArgument();
        QString filename = _item->getParameterName(argument.getName());

        //replace filename
        foreach (const QString parameter, _parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty() && argument.isInput())
        {
            if(!argument.isIterator())
            {
                code += QString("%1.inputs.%3 = %4\n").arg(nodeName, argument.getArgument(s_thisLanguage), filename);
            }
            else if(pair->getInputPort()->getConnections().length() == 0)
            {
                keyValuePairs << QString("('%1', %2)").arg(argument.getArgument(s_thisLanguage), filename);
            }
        }
    }

    if(keyValuePairs.length() != 0)
    {
        code += QString("%1.iterables = [%2]\n").arg(nodeName, keyValuePairs.join(", "));
    }

    code += "\n";
    return code;
}

QStringList NipypeStupidExceptions::getMapNodeFields(
        const NodeTreeItem* _item
        ) const
{
    QStringList iterFields;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        if(pair->isIterator() && pair->getInputPort()->getConnections().length() != 0)
        {
            iterFields << pair->getArgument().getArgument(s_thisLanguage);
        }
    }
    return iterFields;
}

NipypeStupidExceptions::~NipypeStupidExceptions()
{

}
