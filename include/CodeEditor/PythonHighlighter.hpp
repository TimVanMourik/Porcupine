#ifndef PYTHONHIGHLIGHTER_HPP
#define PYTHONHIGHLIGHTER_HPP

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

#endif // PYTHONHIGHLIGHTER_HPP
