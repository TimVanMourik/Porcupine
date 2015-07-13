#include "MatlabHighlighter.hpp"

MatlabHighlighter::MatlabHighlighter(
        QTextDocument* _parent
        ) :
    SyntaxHighlighter(_parent)
{
    ///@todo set font type to standard MATLAB font
//    setFont(QFont("MonoSpace"));

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
                    << "\\bclassdef\\b" << "\\bcontinue\\b" << "\\belse\\b"
                    << "\\belseif\\b" << "\\bend\\b" << "\\bfor\\b"
                    << "\\bfunction\\b" << "\\bglobal\\b" << "\\bif\\b"
                    << "\\botherwise\\b" << "\\bparfor\\b" << "\\bpersistent\\b"
                    << "\\breturn\\b" << "\\bspmd\\b" << "\\bswitch\\b"
                    << "\\btry\\b" << "\\bwhile\\b";

    foreach(const QString& pattern, keywordPatterns)
    {
        addHighlightRule(QRegExp(pattern), keywordFormat);
    }

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(Qt::darkMagenta);
    addHighlightRule(QRegExp("\'.*\'"), quotationFormat);

    QTextCharFormat functionFormat;
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    addHighlightRule(QRegExp("\\b[A-Za-z0-9_]+(?=\\()"), functionFormat);

    ///@todo this one doesn't work yet
    QTextCharFormat thickSingleLineCommentFormat;
    functionFormat.setFontWeight(QFont::Bold);
    thickSingleLineCommentFormat.setForeground(Qt::darkGreen);
    addHighlightRule(QRegExp("%%[^\n]*"), thickSingleLineCommentFormat);

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    addHighlightRule(QRegExp("%[^\n]*"), singleLineCommentFormat);
}

MatlabHighlighter::~MatlabHighlighter()
{

}

