#ifndef MATLABHIGHLIGHTER_H
#define MATLABHIGHLIGHTER_H

#include "SyntaxHighlighter.hpp"

class MatlabHighlighter : public SyntaxHighlighter
{
public:
    MatlabHighlighter(
            QTextDocument* _parent = 0
            );
    ~MatlabHighlighter(
            );
};

#endif // MATLABHIGHLIGHTER_H
