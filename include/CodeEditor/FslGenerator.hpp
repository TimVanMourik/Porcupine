#ifndef FSLGENERATOR_HPP
#define FSLGENERATOR_HPP

#include "CodeGenerator.hpp"

class FslGenerator : public CodeGenerator
{
public:
    //
    FslGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~FslGenerator(
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

#endif // FSLGENERATOR_HPP
