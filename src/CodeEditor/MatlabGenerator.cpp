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
    Q_UNUSED(_item);
    return QString();
}

MatlabGenerator::~MatlabGenerator()
{

}

