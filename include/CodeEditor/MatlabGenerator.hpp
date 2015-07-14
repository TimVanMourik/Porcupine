#ifndef MATLABGENERATOR_H
#define MATLABGENERATOR_H

#include "CodeGenerator.hpp"

class MatlabGenerator : public CodeGenerator
{
public:
    //
    MatlabGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~MatlabGenerator();
private:
    QString itemToCode(
            const NodeTreeItem* _item
            ) const;
};

#endif // MATLABGENERATOR_H
