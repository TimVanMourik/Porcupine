#include "SpmGenerator.hpp"

SpmGenerator::SpmGenerator() :
    CodeGenerator(),
    m_batchNumber(1)
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
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
        m_batchNumber++;
    }
    code.append("\nspm_jobman('run', matlabbatch);");
    m_batchNumber = 1;
    return code;
}

QString SpmGenerator::itemToCode(
        const NodeTreeItem* _item
        )
{
    const NodeSetting* nodeSetting = _item->getNodeSetting();
    QString code("");
    if(nodeSetting->getTitle().getArgument("SPM").isEmpty())
    {
//        return QString("% This function cannot be converted to SPM code\n\n");
        return QString("");
    }

    code.append("% ");
    code.append(nodeSetting->getTitle().getComment("SPM"));
    code.append("\n");

    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }

    //add function
//    code.append("\n");
    //
    return code;
}

QString SpmGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{

    QString code("");
    QString matlabbatch = QString("matlabbatch{%1}").arg(m_batchNumber);
    QString fileName = _item->getFileName(_argument.getName());
//    if(!_argument.getArgument("SPM").isEmpty() && !fileName.isEmpty())
    {
//        code.append(matlabbatch);
//        code.append(".");
        code.append(_argument.getArgument("SPM").replace("\\n", "\n").arg(m_batchNumber).arg(fileName));
//        code.append(" = ");
//        code.append(fileName);
//        code.append(";");
        code.append("\n");
    }
    return code;
}

SpmGenerator::~SpmGenerator()
{

}

