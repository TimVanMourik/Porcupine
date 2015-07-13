#include <QTextEdit>

#include "BashHighlighter.hpp"
#include "CodeEditor.hpp"
#include "MatlabHighlighter.hpp"
#include "PythonHighlighter.hpp"

CodeEditor::CodeEditor(
        QWidget* _parent
        ) :
    QTabWidget(_parent)
{
    QTextEdit* matlabEditor = new QTextEdit(this);
    new MatlabHighlighter(matlabEditor->document());
    addTab(matlabEditor, tr("MATLAB"));

    QTextEdit* pythonEditor = new QTextEdit(this);
    new PythonHighlighter(pythonEditor->document());
    addTab(pythonEditor, tr("Python"));

    QTextEdit* bashEditor = new QTextEdit(this);
    new BashHighlighter(bashEditor->document());
    addTab(bashEditor, tr("Bash"));
}

CodeEditor::~CodeEditor()
{

}

