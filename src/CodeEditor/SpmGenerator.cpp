#include "SpmGenerator.hpp"

SpmGenerator::SpmGenerator() :
    CodeGenerator()
{
}

QString SpmGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    QString code("%SPM batch generator. Warning. Here be dragons.\n");

    code.append("spm_jobman('initcfg');\n");
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

