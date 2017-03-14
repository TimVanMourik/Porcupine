/*  Copyright (C) Tim van Mourik, 2014-2016
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

#include "FieldtripGenerator.hpp"

FieldtripGenerator::FieldtripGenerator() :
    CodeGenerator(),
    m_configurationVariable("cfg")
{

}

QString FieldtripGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList
            )
{
    Q_UNUSED(_linkList);
    QString code;
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
    }
    return code;
}

QString FieldtripGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    if(nodeSetting->getTitle().getArgument("MATLAB").isEmpty())
    {
//        return QString("% This function cannot be converted to MATLAB code\n");
        return QString("");
    }

    code.append("%% ");
    code.append(nodeSetting->getTitle().getComment("MATLAB"));
    code.append("\n");
    code.append(m_configurationVariable).append(" = [];\n");

    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
//        _item->getFileName()
        code.append(argumentToCode(argument, _item));
    }

    //add function
    code.append(nodeSetting->getTitle().getArgument("MATLAB"));
    code.append("(");
    code.append(m_configurationVariable);
    code.append(");");
    code.append("\n\n");
    //
//    code.append('%1(%2)').arg(nodeSetting->getTitle().getArgument("MATLAB"), argument);
    return code;
}

QString FieldtripGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    QString fileName = _item->getFileName(_argument.getName());
    if(!_argument.getArgument("MATLAB").isEmpty() && !fileName.isEmpty())
    {
//        code.append(m_configurationVariable);
//        code.append(".");
//        code.append(_argument.getArgument("MATLAB"));
//        code.append(" = ");
//        code.append(fileName);
//        code.append(";");
        code.append(QString("%1.%2 = %3;\n").arg(m_configurationVariable, _argument.getArgument("MATLAB"), fileName));
        if(!_argument.getComment("MATLAB").isEmpty())
        {
            code.append("\t% ");
            code.append(_argument.getComment("MATLAB"));
        }
        code.append("\n");
    }
    return code;
}

FieldtripGenerator::~FieldtripGenerator()
{

}

