#include "TvmGenerator.hpp"

TvmGenerator::TvmGenerator() :
    CodeGenerator(),
    m_configurationVariable("cfg")
{

}

QString TvmGenerator::generateCode(
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

QString TvmGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    if(nodeSetting->getTitle().getArgument("MATLAB").isEmpty())
    {
        return QString("");
    }

    code.append(QString("%% %1\n").arg(nodeSetting->getTitle().getComment("MATLAB")));
    code.append(QString("%1 = [];\n").arg(m_configurationVariable));

    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }

    //add function
    code.append(QString("%1(%2);\n\n").arg(nodeSetting->getTitle().getArgument("MATLAB"), m_configurationVariable));
    //
    return code;
}

QString TvmGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    QString fileName = _item->getFileName(_argument.getName());
    if(!_argument.getArgument("MATLAB").isEmpty() && !fileName.isEmpty())
    {
        code.append(QString("%1.%2 = %3;").arg(m_configurationVariable, _argument.getArgument("MATLAB"), fileName));
        if(!_argument.getComment("MATLAB").isEmpty())
        {
            code.append("\t% ");
            code.append(_argument.getComment("MATLAB"));
        }
        code.append("\n");
    }
    return code;
}

TvmGenerator::~TvmGenerator()
{

}

