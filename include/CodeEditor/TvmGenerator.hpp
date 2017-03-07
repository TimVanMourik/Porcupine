#ifndef TVMGENERATOR_HPP
#define TVMGENERATOR_HPP

#include "CodeGenerator.hpp"

class TvmGenerator : public CodeGenerator
{
public:
    //
    TvmGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~TvmGenerator(
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

#endif // TVMGENERATOR_HPP
