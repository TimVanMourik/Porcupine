#ifndef PYTHONHIGHLIGHTER_H
#define PYTHONHIGHLIGHTER_H

#include "SyntaxHighlighter.hpp"

class PythonHighlighter : public SyntaxHighlighter
{
public:
    //
    PythonHighlighter(
            QTextDocument* _parent = 0
            );
    //
    ~PythonHighlighter();
};

#endif // PYTHONHIGHLIGHTER_H
