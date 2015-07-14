#include "BashGenerator.hpp"

BashGenerator::BashGenerator() :
    CodeGenerator()
{

}

QString BashGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList
            )
{
    Q_UNUSED(_nodeList);
    QString code("No Bash code converter implemented :(\n");
    return code;
}

BashGenerator::~BashGenerator()
{

}

