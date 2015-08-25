#include "BashGenerator.hpp"

BashGenerator::BashGenerator() :
    CodeGenerator()
{

}

QString BashGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    QString code;
    code.append("");
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
    }
    return code;
}


QString BashGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("#!/bin/bash\n\n");
    if(nodeSetting->getTitle().getArgument("Bash").isEmpty())
    {
        return QString("# This function cannot be converted to Bash code\n");
    }
    //add function comment
    code.append("# ");
    code.append(nodeSetting->getTitle().getComment("Bash"));
    code.append("\n");

    //add function
    code.append(nodeSetting->getTitle().getArgument("Bash"));

//    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }
    code.append(";\n");
    return code;
}

QString BashGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    code.append(" ");
    code.append(_argument.getArgument("Bash"));
    code.append(" ");
    code.append(_item->getFileName(_argument.getName()));
    return code;
}

BashGenerator::~BashGenerator()
{

}

