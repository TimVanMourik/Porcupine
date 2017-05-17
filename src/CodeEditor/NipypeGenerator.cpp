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

#include "CodeEditor.hpp"
#include "NipypeGenerator.hpp"
#include "Port.hpp"
#include "PortPair.hpp"

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
    ///@todo check if there is at least one NiPype module in the scene

    QString code("#This is a NiPype generator. Warning, here be dragons.\n");
    writePreamble(code);
    writeParameters(code);
    writeNodes(code, _nodeList);
    writeLinks(code, _linkList);

    code.append("\n#Run the workflow\n");
    code.append("analysisflow.run()\n");

    return code;
}

QString NipypeGenerator::itemToCode(
        const NodeTreeItem* _item,
        const QMap<QString, QString>& parameters
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    if(nodeSetting->getTitle().getArgument("NiPype").isEmpty())
    {
        return QString("");
    }

    QString nodeName = QString("NodeHash_%1").arg(QString::number((quint64) _item->getNode(), 16));
    code.append(QString("#%1\n").arg(nodeSetting->getTitle().getComment("NiPype")));
    code.append(QString("%1 = pe.Node(interface = %2, ").arg(nodeName, nodeSetting->getTitle().getArgument("NiPype")));
    code.append(QString("name = 'NodeName_%1')\n").arg(QString::number((quint64) _item->getNode(), 16)));
    foreach (Argument argument, nodeSetting->getPorts())
    {
        QString filename = _item->getFileName(argument.getName());
        //replace filename
        foreach (const QString parameter, parameters.keys())
        {
            if(filename.contains(QString("$").append(parameter)))
            {
                filename = filename.replace(QString("$").append(parameter), parameter);
            }
        }

        if(!filename.isEmpty())
        {
            if(argument.getType() == Argument::INPUT || argument.getType() == Argument::INOUT || argument.getType() == Argument::HIDDEN || argument.getType() == Argument::SECRET)
            {
                code.append(QString("%1.inputs.%2 = %3\n").arg(nodeName, argument.getArgument("NiPype"), filename));
            }
        }

        if(!filename.isEmpty())
        {
            if(argument.getType() == Argument::OUTPUT || argument.getType() == Argument::INOUT)
            {
                code.append(QString("%1.outputs.%2 = %3\n").arg(nodeName, argument.getArgument("NiPype"), filename));
            }
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
    QString sourceAttribute(_link->getPortFrom()->getPortPair()->getArgument()->getArgument("NiPype"));
    QString destinationAttribute(_link->getPortTo()->getPortPair()->getArgument()->getArgument("NiPype"));
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

