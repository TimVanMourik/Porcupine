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

#include "SpmGenerator.hpp"

SpmGenerator::SpmGenerator() :
    CodeGenerator()
{
}

QString SpmGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList
            )
{
    Q_UNUSED(_linkList);
    QString code("%SPM batch generator. Warning. Here be dragons.\n\n");
    code.append("matlabbatch = cell(0);\n");
    code.append("batchNumber = 0;\n");
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
    }
    code.append("\nspm_jobman('run', matlabbatch);");
    return code;
}

QString SpmGenerator::itemToCode(
        const NodeTreeItem* _item
        )
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    code.append("\n% ");
    if((nodeSetting->getTitle().getComment("SPM").isEmpty()))
    {
        return QString("");
    }
    code.append(nodeSetting->getTitle().getComment("SPM"));
    code.append("\nbatchNumber = batchNumber + 1;\n");
    code.append("mainBatch = batchNumber;\n");

    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }
    return code;
}

QString SpmGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    QString fileName = _item->getFileName(_argument.getName());
    code.append(_argument.getArgument("SPM").replace("\\n", "\n").replace("\\t", "\t").arg(fileName));
    code.append("\n");

    return code;
}

SpmGenerator::~SpmGenerator()
{
}

