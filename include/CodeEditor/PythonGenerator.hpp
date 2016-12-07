#ifndef PYTHONGENERATOR_HPP
#define PYTHONGENERATOR_HPP

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

#endif // PYTHONGENERATOR_HPP
