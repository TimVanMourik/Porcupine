#ifndef CODEEDITOR_HPP
#define CODEEDITOR_HPP

#include <QTabWidget>

class CodeGenerator;
class Link;
class NodeTreeItem;
class QTextEdit;

class CodeEditor : public QTabWidget
{
public:
    //
    CodeEditor(
            QWidget* _parent = 0
            );
    //
    void generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~CodeEditor(
            );
private:
    //
    void setupMatlabEditor(
            );
    //
    void setupSpmEditor(
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

#endif // CODEEDITOR_HPP
