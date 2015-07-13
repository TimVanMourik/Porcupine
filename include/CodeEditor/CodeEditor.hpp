#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QTabWidget>

class CodeEditor : public QTabWidget
{
public:
    //
    CodeEditor(
            QWidget* _parent
            );
    //
    ~CodeEditor(
            );
};

#endif // CODEEDITOR_H
