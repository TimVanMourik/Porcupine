/*  Copyright (C) Tim van Mourik, 2014-2017
    Copyright (C) Tim van Mourik, 2017, DCCN
    All rights reserved

 This file is part of the Porcupine pipeline tool, see
 https://github.com/TimVanMourik/Porcupine for the documentation and
 details.

    This toolbox is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the fmri analysis toolbox. If not, see
    <http://www.gnu.org/licenses/>.
*/

#include <functional>

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "CodeEditor.hpp"
#include "NipypeStupidExceptions.hpp"
#include "NipypeGenerator.hpp"
#include "Port.hpp"
#include "PortPair.hpp"

const QString NipypeGenerator::s_thisLanguage("NiPype");
QStringList NipypeGenerator::s_exceptionNodes;

NipypeGenerator::NipypeGenerator(
        CodeEditor* _editor
        ) :
    CodeGenerator(_editor)
{
    s_exceptionNodes << "utility.IdentityInterface" << "io.SelectFiles" << "io.MySQLSink" << "io.SQLiteSink";
}

QString NipypeGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList
            )
{
    ///@todo check if there is at least one NiPype module in the scene for given module
    QString code("#This is a NiPype generator. Warning, here be dragons.\n");
    writePreamble(code, _nodeList);
    writeParameters(code);
    writeNodes(code, _nodeList);
    writeLinks(code, _linkList);

    code += "\n#Run the workflow\n";
    code += "analysisflow.run()\n";

    return code;
}

QStringList NipypeGenerator::getMapNodeFields(
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

QString NipypeGenerator::itemToCode(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& _parameters
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage).isEmpty()) return QString("");

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));

    if(s_exceptionNodes.contains(title.m_argumentName))
    {
        NipypeStupidExceptions& exception = NipypeStupidExceptions::getInstance();
        return exception.exceptionNodetoCode(_item, _parameters);
    }
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

    code += QString("(interface = %2, ").arg(title.getArgument(s_thisLanguage));
    code += QString("name = 'NodeName_%1'").arg(QString::number((quint64) _item->getNode(), 16));

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
        QString filename = _item->getParameterName(argument.m_argumentName);

        //replace filename
        foreach (const QString parameter, _parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty() && argument.m_isInput)
        {
            if(!argument.m_isIterator)
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

QString NipypeGenerator::linkToCode(
        const Link* _link
        ) const
{
    QString code("");
    QString source =  QString("NodeHash_%1").arg(QString::number((quint64) _link->getPortFrom()->getNode(), 16));
    QString destination =  QString("NodeHash_%1").arg(QString::number((quint64) _link->getPortTo()->getNode(), 16));
    QString sourceAttribute(   _link->getPortFrom()->getPortPair()->getArgument().m_argumentName);
    QString destinationAttribute(_link->getPortTo()->getPortPair()->getArgument().m_argumentName);
    code += QString("analysisflow.connect(%1, '%2', %3, '%4')\n").arg(source, sourceAttribute, destination, destinationAttribute);

    return code;
}

void NipypeGenerator::writePreamble(
        QString& io_code,
        const QList<NodeTreeItem*>& _nodeList
        )
{
    ///@todo make module import dependent on scene nodes
    io_code += "import nipype\n";
    io_code += "import nipype.pipeline as pe\n";
    QStringList categories;
    foreach(NodeTreeItem* item, _nodeList)
    {
        QJsonObject object = item->getJson();
        QString category = object["title"].toObject()["code"].toArray().first().toObject()["argument"].toString();
        QStringList splitted = category.split(".");
        category = splitted.first();
        if(!categories.contains(category))
        {
            categories << category;
        }
    }
    foreach (QString category, categories)
    {
        io_code += QString("import nipype.interfaces.%1 as %1\n").arg(category);
    }
    io_code += "\n";
}

void NipypeGenerator::writeParameters(
        QString& io_code
        )
{
    QMap<QString, QString> parameters = m_editor->getParameters();
    foreach(const QString parameter, parameters.keys())
    {
        io_code += QString("%1 = %2\n").arg(parameter, parameters[parameter]);
    }
    io_code += "\n";
}

void NipypeGenerator::writeNodes(
        QString& io_code,
        const QList<NodeTreeItem*>& _nodeList
        )
{
    QMap<QString, QString> parameters = m_editor->getParameters();
    foreach(const NodeTreeItem* item, _nodeList)
    {
        io_code += itemToCode(item, parameters);
    }
}

void NipypeGenerator::writeLinks(
        QString& io_code,
        const QVector<const Link*>& _linkList
        )
{
    io_code += "#Create a workflow to connect all those nodes\n";
    io_code += "analysisflow = nipype.Workflow('MyWorkflow')\n";
    foreach(const Link* link, _linkList)
    {
        io_code += linkToCode(link);
    }
}

NipypeGenerator::~NipypeGenerator()
{
}

