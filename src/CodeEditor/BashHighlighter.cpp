#include "BashHighlighter.hpp"

BashHighlighter::BashHighlighter(
        QTextDocument* _parent
        ) :
    SyntaxHighlighter(_parent)
{
//    HighlightingRule rule;

//    m_keywordFormat.setForeground(Qt::darkBlue);
//    m_keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
//                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
//                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
//                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
//                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
//                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
//                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
//                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
//                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
//                    << "\\bvoid\\b" << "\\bvolatile\\b";

//    foreach(const QString& pattern, keywordPatterns)
//    {
//        rule.pattern = QRegExp(pattern);
//        rule.format = m_keywordFormat;
//        m_highlightingRules.append(rule);
//    }
//    m_classFormat.setFontWeight(QFont::Bold);
//    m_classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
//    rule.format = m_classFormat;
//    m_highlightingRules.append(rule);

//    m_singleLineCommentFormat.setForeground(Qt::red);
//    rule.pattern = QRegExp("//[^\n]*");
//    rule.format = m_singleLineCommentFormat;
//    m_highlightingRules.append(rule);

//    m_multiLineCommentFormat.setForeground(Qt::red);

//    m_quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegExp("\".*\"");
//    rule.format = m_quotationFormat;
//    m_highlightingRules.append(rule);

//    m_functionFormat.setFontItalic(true);
//    m_functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = m_functionFormat;
//    m_highlightingRules.append(rule);

//    m_commentStartExpression = QRegExp("/\\*");
//    m_commentEndExpression = QRegExp("\\*/");
}

BashHighlighter::~BashHighlighter()
{

}

