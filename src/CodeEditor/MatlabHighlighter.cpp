#include "MatlabHighlighter.hpp"

MatlabHighlighter::MatlabHighlighter(
        QTextDocument* _parent
        ) :
    SyntaxHighlighter(_parent)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setFont(QFont("Courier", 10));
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywords;
    keywords << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
                    << "\\bclassdef\\b" << "\\bcontinue\\b" << "\\belse\\b"
                    << "\\belseif\\b" << "\\bend\\b" << "\\bfor\\b"
                    << "\\bfunction\\b" << "\\bglobal\\b" << "\\bif\\b"
                    << "\\botherwise\\b" << "\\bparfor\\b" << "\\bpersistent\\b"
                    << "\\breturn\\b" << "\\bspmd\\b" << "\\bswitch\\b"
                    << "\\btry\\b" << "\\bwhile\\b";

    foreach(const QString& pattern, keywords)
    {
        addHighlightRule(QRegExp(pattern), keywordFormat);
    }

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(Qt::darkMagenta);
    addHighlightRule(QRegExp("\'.*\'"), quotationFormat);

//    QTextCharFormat functionFormat;
//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    addHighlightRule(QRegExp("\\b[A-Za-z0-9_]+(?=\\()"), functionFormat);

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    addHighlightRule(QRegExp("%[^\n]*"), singleLineCommentFormat);

    QTextCharFormat thickSingleLineCommentFormat;
    thickSingleLineCommentFormat.setFontWeight(QFont::Bold);
    thickSingleLineCommentFormat.setForeground(Qt::darkGreen);
    addHighlightRule(QRegExp("%% [^\n]*"), thickSingleLineCommentFormat);
}

MatlabHighlighter::~MatlabHighlighter()
{

}

