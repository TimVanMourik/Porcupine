#include "PythonGenerator.hpp"

PythonGenerator::PythonGenerator() :
    CodeGenerator()
{

}

QString PythonGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    Q_UNUSED(_nodeList);
    QString code("No Python code converter implemented :(\n");
    return code;
}

PythonGenerator::~PythonGenerator()
{

}

