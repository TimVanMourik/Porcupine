#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QTabWidget>

class CodeGenerator;
class NodeTreeItem;
class QTextEdit;

class CodeEditor : public QTabWidget
{
public:
    //
    CodeEditor(
            QWidget* _parent
            );
    //
    void generateCode(
            const QList<NodeTreeItem*>& _nodeList
            );
    //
    ~CodeEditor(
            );
private:
    //
    void setupMatlabEditor(
            );
    //
    void setupBashEditor(
            );
    //
    void setupPythonEditor(
            );
    //
    QMap<QString, QTextEdit*> m_textEditors;
    //
    QMap<QString, CodeGenerator*> m_codeGenerators;
    //
    QStringList m_programmingLanguages;
};

#endif // CODEEDITOR_H
