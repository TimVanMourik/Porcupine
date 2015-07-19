#include "MatlabGenerator.hpp"

MatlabGenerator::MatlabGenerator() :
    CodeGenerator(),
    m_configurationWord("cfg")
{

}

QString MatlabGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    QString code;
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
    }

//    QString code("Generating MATLAB code\n");
    return code;
}

QString MatlabGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    code.append("%% ");
    code.append(nodeSetting->getTitle().getComment("MATLAB"));
    code.append("\n");

    //add input
    foreach (Argument argument, nodeSetting->getInput())
    {
//        _item->getFileName()
        code.append(argumentToCode(argument, _item));
    }
    //add input-output
    foreach (Argument argument, nodeSetting->getInOut())
    {
        code.append(argumentToCode(argument, _item));
    }
    //add output
    foreach (Argument argument, nodeSetting->getOutput())
    {
        code.append(argumentToCode(argument, _item));
    }

    //add function
    code.append(nodeSetting->getTitle().getArgument("MATLAB"));
    code.append("(");
    code.append(m_configurationWord);
    code.append(");");
    code.append("\n\n");
    //
    return code;
}

#include <iostream>
QString MatlabGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    if(!_argument.getArgument("MATLAB").isEmpty())
    {
        code.append(m_configurationWord);
        code.append(".");
        code.append(_argument.getArgument("MATLAB"));
        code.append(" = ");
        QString fileName = _item->getFileName(_argument.getName());
        code.append(fileName);
        code.append(";");
        if(!_argument.getComment("MATLAB").isEmpty())
        {
            code.append("\t% ");
            code.append(_argument.getComment("MATLAB"));
        }
        // append given name
    }
    code.append("\n");
    return code;
}

MatlabGenerator::~MatlabGenerator()
{

}

