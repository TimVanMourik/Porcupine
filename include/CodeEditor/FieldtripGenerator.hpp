#ifndef FIELDTRIPGENERATOR_HPP
#define FIELDTRIPGENERATOR_HPP

#include "CodeGenerator.hpp"

class FieldtripGenerator : public CodeGenerator
{
public:
    //
    FieldtripGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~FieldtripGenerator(
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
    //
    QString m_configurationVariable;
};

#endif // FIELDTRIPGENERATOR_HPP
