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
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
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
