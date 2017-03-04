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
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~MatlabGenerator(
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

#endif // MATLABGENERATOR_H
