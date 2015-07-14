#include "BashHighlighter.hpp"

BashHighlighter::BashHighlighter(
        QTextDocument* _parent
        ) :
    SyntaxHighlighter(_parent)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setFont(QFont("Courier", 10));
    keywordFormat.setForeground(Qt::darkRed);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywords;
    keywords << "\\bif\\b" << "\\bthen\\b" << "\\belse\\b"
                    << "\\belif\\b" << "\\bfi\\b" << "\\bcase\\b"
                    << "\\besac\\b" << "\\bfor\\b" << "\\bselect\\b"
                    << "\\bwhile\\b" << "\\buntil\\b" << "\\bdo\\b"
                    << "\\bdone\\b" << "\\bin\\b" << "\\bfunction\\b"
                    << "\\btime\\b";

    foreach(const QString& pattern, keywords)
    {
        addHighlightRule(QRegExp(pattern), keywordFormat);
    }

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::darkBlue);
    addHighlightRule(QRegExp("#[^\n]*"), singleLineCommentFormat);
}

BashHighlighter::~BashHighlighter()
{

}

