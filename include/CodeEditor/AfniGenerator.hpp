#ifndef AFNIGENERATOR_HPP
#define AFNIGENERATOR_HPP

#include "CodeGenerator.hpp"

class AfniGenerator : public CodeGenerator
{
public:
    //
    AfniGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~AfniGenerator(
            );
private:
    QString itemToCode(
            const NodeTreeItem* _item
            ) const;
    //
    QString argumentToCode(
            const Argument& _argument,
            const NodeTreeItem* _item
            ) const;
};

#endif // AFNIGENERATOR_HPP
