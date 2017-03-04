#ifndef BASHGENERATOR_H
#define BASHGENERATOR_H

#include "CodeGenerator.hpp"

class BashGenerator : public CodeGenerator
{
public:
    //
    BashGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~BashGenerator(
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

#endif // BASHGENERATOR_H
