#include "PythonHighlighter.hpp"

PythonHighlighter::PythonHighlighter(
        QTextDocument* _parent
        ) :
    SyntaxHighlighter(_parent)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywords;
    keywords << "\\band\\b" << "\\bas\\b" << "\\bassert\\b" << "\\bbreak\\b"
             << "\\bclass\\b" << "\\bcontinue\\b" << "\\bdef\\b" << "\\bdel\\b"
             << "\\belif\\b" << "\\belse\\b" << "\\bexcept\\b" << "\\bexec\\b"
             << "\\bfinally\\b" << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
             << "\\bif\\b" << "\\bimport\\b" << "\\bin\\b" << "\\bis\\b"
             << "\\blambda\\b" << "\\bnot\\b" << "\\bor\\b" << "\\bpass\\b"
             << "\\bprint\\b" << "\\braise\\b" << "\\breturn\\b" << "\\btry\\b"
             << "\\bwhile\\b" << "\\bwith\\b" << "\\byield";
    foreach(const QString& pattern, keywords)
    {
        addHighlightRule(QRegExp(pattern), keywordFormat);
    }


    QTextCharFormat typeNameFormat;
    typeNameFormat.setForeground(Qt::red);
    typeNameFormat.setFontWeight(QFont::Bold);
    QStringList typeNames;
    typeNames << "\\int\\b" << "\\bfloat\\b" << "\\bstr\\b" << "\\bbytes\\b"
             << "\\bbytearray\\b" << "\\blist\\b" << "\\btuple\\b" << "\\brange\\b";
    foreach(const QString& pattern, typeNames)
    {
        addHighlightRule(QRegExp(pattern), typeNameFormat);
    }

//    QTextCharFormat digitFormat;
//    digitFormat.setForeground(Qt::green);
//    addHighlightRule(QRegExp("[0-9]"), digitFormat);

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(Qt::green);
    addHighlightRule(QRegExp("\".*\""), quotationFormat);

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::darkRed);
    addHighlightRule(QRegExp("#[^\n]*"), singleLineCommentFormat);
}

PythonHighlighter::~PythonHighlighter()
{

}

