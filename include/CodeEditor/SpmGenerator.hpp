#ifndef SPMGENERATOR_HPP
#define SPMGENERATOR_HPP

#include "CodeGenerator.hpp"

class SpmGenerator : public CodeGenerator
{
public:
    //
    SpmGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~SpmGenerator(
            );
private:
    //
    int m_batchNumber;
    //
    QString itemToCode(
            const NodeTreeItem* _item
            );
    //
    QString argumentToCode(
            const Argument& _argument,
            const NodeTreeItem* _item
            ) const;

};

#endif // SPMGENERATOR_HPP
