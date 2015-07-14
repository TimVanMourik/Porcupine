#ifndef PYTHONGENERATOR_H
#define PYTHONGENERATOR_H

#include "CodeGenerator.hpp"

class PythonGenerator : public CodeGenerator
{
public:
    //
    PythonGenerator();
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~PythonGenerator();
};

#endif // PYTHONGENERATOR_H
