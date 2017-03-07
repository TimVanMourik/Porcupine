#include "AfniGenerator.hpp"

AfniGenerator::AfniGenerator() :
    CodeGenerator()
{

}

QString AfniGenerator::generateCode(
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


QString AfniGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    if(nodeSetting->getTitle().getArgument("Afni").isEmpty())
    {
        return QString("# This function cannot be converted to Bash code\n");
    }
    //add function comment
    code.append("# ");
    code.append(nodeSetting->getTitle().getComment("Afni"));
    code.append("\n");

    //add function
    code.append(nodeSetting->getTitle().getArgument("Afni"));

//    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }
    code.append(";\n");
    return code;
}

QString AfniGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code(" ");
    if(!_argument.getArgument("Afni").isEmpty())
    {
//        code.append(" ");
        code.append(_argument.getArgument("Afni"));
    }
    code.append(_item->getFileName(_argument.getName()));
    return code;
}

AfniGenerator::~AfniGenerator()
{

}

