#ifndef BASHHIGHLIGHTER_H
#define BASHHIGHLIGHTER_H

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

#endif // BASHHIGHLIGHTER_H
