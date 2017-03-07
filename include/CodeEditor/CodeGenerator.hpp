#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <QList>
#include <QString>

#include "NodeSetting.hpp"
#include "NodeTreeItem.hpp"

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

#endif // CODEGENERATOR_HPP
