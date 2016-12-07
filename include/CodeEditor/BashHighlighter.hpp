#ifndef BASHHIGHLIGHTER_HPP
#define BASHHIGHLIGHTER_HPP

#include "SyntaxHighlighter.hpp"

class BashHighlighter : public SyntaxHighlighter
{
public:
    //
    BashHighlighter(
            QTextDocument* _parent = 0
            );
    //
    ~BashHighlighter();
};

#endif // BASHHIGHLIGHTER_HPP
