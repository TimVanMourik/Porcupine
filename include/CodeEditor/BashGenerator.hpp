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
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~BashGenerator();
};

#endif // BASHGENERATOR_H
