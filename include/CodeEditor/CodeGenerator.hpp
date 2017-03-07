#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <QList>
#include <QString>

#include "NodeSetting.hpp"
#include "NodeTreeItem.hpp"

class Link;

class CodeGenerator
{
public:
    //
    CodeGenerator();
    //
    virtual QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            ) = 0;
    //
    ~CodeGenerator();
};

#endif // CODEGENERATOR_HPP
