#include "SpmGenerator.hpp"

SpmGenerator::SpmGenerator() :
    CodeGenerator(),
    m_batchNumber(1)
{

}

QString SpmGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    QString code("%SPM batch generator. Warning. Here be dragons.\n");

    code.append("batchNumber = 0;\n");
    code.append("matlabbatch = cell(0);\n\n");
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code.append(itemToCode(item));
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
    code.append("% ");
    if((nodeSetting->getTitle().getComment("SPM").isEmpty()))
    {
        return QString("");
    }
    code.append(nodeSetting->getTitle().getComment("SPM"));
    code.append("\nbatchNumber = batchNumber + 1;\n");

    //add input
    foreach (Argument argument, nodeSetting->getPorts())
    {
        code.append(argumentToCode(argument, _item));
    }

    //add function
//    code.append("\n");
    //
    m_batchNumber++;
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
        code.append(_argument.getArgument("SPM").replace("\\n", "\n").replace("\\t", "\t").arg(fileName));
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

