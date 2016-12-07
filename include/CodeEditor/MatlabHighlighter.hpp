#ifndef MATLABHIGHLIGHTER_HPP
#define MATLABHIGHLIGHTER_HPP

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

#endif // MATLABHIGHLIGHTER_HPP
