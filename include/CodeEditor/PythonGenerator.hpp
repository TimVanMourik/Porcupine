#ifndef PYTHONGENERATOR_H
#define PYTHONGENERATOR_H

#include "CodeGenerator.hpp"
#include "Link.hpp"

class PythonGenerator : public CodeGenerator
{
public:
    //
    PythonGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~PythonGenerator();
private:
    //
    QString linkToCode(
            const Link* _link
            ) const;
    //
    QString itemToCode(
            const NodeTreeItem* _item
            ) const;
    //
    QString argumentToCode(
            const Argument& _argument,
            const NodeTreeItem* _item
            ) const;
};

#endif // PYTHONGENERATOR_H
