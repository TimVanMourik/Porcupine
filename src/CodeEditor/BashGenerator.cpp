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
    QString code("");
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
    code.append(" ");

//    //add input
    foreach (Argument argument, nodeSetting->getInput())
    {
        code.append(argument.getArgument("Bash"));
        code.append(" ");
        code.append(_item->getFileName(argument.getName()));
        code.append(" ");
    }
    //add input-output
    foreach (Argument argument, nodeSetting->getInOut())
    {
        code.append(argument.getArgument("Bash"));
        code.append(" ");
        code.append(_item->getFileName(argument.getName()));
        code.append(" ");
    }
    //add output
    foreach (Argument argument, nodeSetting->getOutput())
    {
        code.append(argument.getArgument("Bash"));
        code.append(" ");
        code.append(_item->getFileName(argument.getName()));
        code.append(" ");
    }
    code.append(";\n");
    return code;
}

BashGenerator::~BashGenerator()
{

}

