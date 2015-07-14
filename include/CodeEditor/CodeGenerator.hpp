#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <QList>
#include <QString>

class NodeTreeItem;

class CodeGenerator
{
public:
    //
    CodeGenerator();
    //
    virtual QString generateCode(
            const QList<NodeTreeItem*>& _nodeList
            ) = 0;
    //
    ~CodeGenerator();
};

#endif // CODEGENERATOR_H
