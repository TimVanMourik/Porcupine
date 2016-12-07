#include "FieldtripGenerator.hpp"

FieldtripGenerator::FieldtripGenerator() :
    CodeGenerator(),
    m_configurationVariable("cfg")
{

}

QString FieldtripGenerator::generateCode(
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
        code.append(m_configurationVariable);
        code.append(".");
        code.append(_argument.getArgument("MATLAB"));
        code.append(" = ");
        code.append(fileName);
        code.append(";");
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

