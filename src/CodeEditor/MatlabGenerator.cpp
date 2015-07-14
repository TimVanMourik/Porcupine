#include "MatlabGenerator.hpp"

MatlabGenerator::MatlabGenerator() :
    CodeGenerator()
{

}

QString MatlabGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    Q_UNUSED(_nodeList);
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
    Q_UNUSED(nodeSetting);
    return QString();
}

MatlabGenerator::~MatlabGenerator()
{

}

