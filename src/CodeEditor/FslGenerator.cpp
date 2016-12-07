#include "FslGenerator.hpp"

FslGenerator::FslGenerator() :
    CodeGenerator()
{

}

QString FslGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
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

