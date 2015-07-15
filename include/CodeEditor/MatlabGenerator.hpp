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
    //
    QString argumentToCode(
            const Argument& _argument,
            const NodeTreeItem* _item
            ) const;
    //
    QString m_configurationWord;
};

#endif // MATLABGENERATOR_H
