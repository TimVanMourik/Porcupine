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

#include <QJsonObject>
#include <QJsonArray>

#include "CodeEditor.hpp"
#include "NipypeGenerator.hpp"
#include "Port.hpp"
#include "PortPair.hpp"

const QString NipypeGenerator::s_thisLanguage("NiPype");

NipypeGenerator::NipypeGenerator(
        CodeEditor* _editor
        ) :
    CodeGenerator(_editor)
{
}

QString NipypeGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList
            )
{
    ///@todo check if there is at least one NiPype module in the scene for given module
    QString code("#This is a NiPype generator. Warning, here be dragons.\n");
    writePreamble(code);
    writeParameters(code);
    writeNodes(code, _nodeList);
    writeLinks(code, _linkList);

    code.append("\n#Run the workflow\n");
    code.append("analysisflow.run()\n");

    return code;
}

QStringList NipypeGenerator::getIteratorFields(
        const NodeTreeItem* _item
        ) const
{
    QStringList iterFields;
    foreach (const PortPair* pair,  _item->getPorts())
    {
        if(pair->isIterator()) iterFields << pair->getArgument().getArgument(s_thisLanguage);
    }
    return iterFields;
}

QString NipypeGenerator::itemToCode(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& parameters
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage).isEmpty()) return QString("");

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));
    code.append(QString("#%1\n").arg(title.getComment(s_thisLanguage)));
    code.append(QString("%1 = pe.").arg(nodeName));

    QStringList iterFields = getIteratorFields(_item);
    if(iterFields.length() == 0) {code.append(QString("Node"));}
    else                         {code.append(QString("MapNode"));}

    code.append(QString("(interface = %2, ").arg(title.getArgument(s_thisLanguage)));
    code.append(QString("name = 'NodeName_%1'").arg(QString::number((quint64) _item->getNode(), 16)));

    if(iterFields.length() == 0) code.append(")\n");
    else                         code.append(QString(", iterfield = ['%1'])\n").arg(iterFields.join("', '")));

    foreach (QJsonValue portObject, json["ports"].toArray())
    {
        Argument argument = Argument(portObject.toObject());
        QString filename = _item->getFileName(argument.getName());
        //replace filename
        foreach (const QString parameter, parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty() && argument.isInput())
        {
            code.append(QString("%1.inputs.%2 = %3\n").arg(nodeName, argument.getArgument(s_thisLanguage), filename));
        }

        if(!filename.isEmpty() && argument.isOutput())
        {
            code.append(QString("%1.outputs.%2 = %3\n").arg(nodeName, argument.getArgument(s_thisLanguage), filename));
        }
    }
    code.append("\n");
    return code;
}

QString NipypeGenerator::linkToCode(
        const Link* _link
        ) const
{
    QString code("");
    QString source =  QString("NodeHash_%1").arg(QString::number((quint64) _link->getPortFrom()->getNode(), 16));
    QString destination =  QString("NodeHash_%1").arg(QString::number((quint64) _link->getPortTo()->getNode(), 16));
    QString sourceAttribute(_link->getPortFrom()->getPortPair()->getArgument().getArgument("NiPype"));
    QString destinationAttribute(_link->getPortTo()->getPortPair()->getArgument().getArgument("NiPype"));
    code.append(QString("analysisflow.connect(%1, '%2', %3, '%4')\n").arg(source, sourceAttribute, destination, destinationAttribute));

    return code;
}

void NipypeGenerator::writePreamble(
        QString& io_code
        )
{
    ///@todo make module import dependent on scene nodes
    io_code.append("import nipype\n");
    io_code.append("import nipype.pipeline as pe\n");
    io_code.append("import nipype.interfaces.fsl as fsl\n");
    io_code.append("import nipype.interfaces.afni as afni\n");
    io_code.append("import nipype.interfaces.spm as spm\n");
    io_code.append("import nipype.interfaces.utility as utility\n\n");

    io_code.append("import nipype\n\n");
}

void NipypeGenerator::writeParameters(
        QString& io_code
        )
{
    QMap<QString, QString> parameters = m_editor->getParameters();
    foreach(const QString parameter, parameters.keys())
    {
        io_code.append(QString("%1 = %2\n").arg(parameter, parameters[parameter]));
    }
    io_code.append("\n");
}

void NipypeGenerator::writeNodes(
        QString& io_code,
        const QList<NodeTreeItem*>& _nodeList
        )
{
    QMap<QString, QString> parameters = m_editor->getParameters();
    foreach(const NodeTreeItem* item, _nodeList)
    {
        io_code.append(itemToCode(item, parameters));
    }
}

void NipypeGenerator::writeLinks(
        QString& io_code,
        const QVector<const Link*>& _linkList
        )
{
    io_code.append("#Create a workflow to connect all those nodes\n");
    io_code.append("analysisflow = nipype.Workflow('MyWorkflow')\n");
    foreach(const Link* link, _linkList)
    {
        io_code.append(linkToCode(link));
    }
}

NipypeGenerator::~NipypeGenerator()
{
}

