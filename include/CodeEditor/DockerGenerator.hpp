#ifndef DOCKERGENERATOR_HPP
#define DOCKERGENERATOR_HPP

#include "CodeGenerator.hpp"

class DockerGenerator : public CodeGenerator
{
public:
    //
    DockerGenerator(
            CodeEditor* _editor = 0
            );
    //
    QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~DockerGenerator(
            );

private:
    static const QString s_thisLanguage;
};

#endif // DOCKERGENERATOR_HPP
