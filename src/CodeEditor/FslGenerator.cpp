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

#include "FslGenerator.hpp"

FslGenerator::FslGenerator() :
    CodeGenerator()
{

}

QString FslGenerator::generateCode(
        const QList<NodeTreeItem*>& _nodeList,
        const QVector<const Link*>& _linkList
        )
{
    Q_UNUSED(_linkList);
    QString code("#!/bin/bash\n\n");
    code.append("");
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
    }
    return code;
}


QString FslGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    if(nodeSetting->getTitle().getArgument("FSL").isEmpty())
    {
        return QString("# This function cannot be converted to Bash code\n");
    }
    //add function comment
    code.append("# ");
    code.append(nodeSetting->getTitle().getComment("FSL"));
    code.append("\n");

    //add function
    code.append(nodeSetting->getTitle().getArgument("FSL"));

//    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }
    code.append(";\n");
    return code;
}

QString FslGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code(" ");
    if(!_argument.getArgument("FSL").isEmpty())
    {
//        code.append(" ");
        code.append(_argument.getArgument("FSL"));
    }
    code.append(_item->getFileName(_argument.getName()));
    return code;
}

FslGenerator::~FslGenerator()
{

}

