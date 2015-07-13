#include "SyntaxHighlighter.hpp"

SyntaxHighlighter::SyntaxHighlighter(
        QTextDocument* _parent
        ) :
    QSyntaxHighlighter(_parent)
{
}

void SyntaxHighlighter::highlightBlock(
        const QString& _text
        )
{
    foreach(const HighlightingRule& rule, m_highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(_text);
        while(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(_text, index + length);
        }
    }
    setCurrentBlockState(0);
}

void SyntaxHighlighter::addHighlightRule(
        const QRegExp& _expression,
        const QTextCharFormat& _format
        )
{
    HighlightingRule rule;
    rule.pattern = _expression;
    rule.format = _format;
    m_highlightingRules.append(rule);
}

SyntaxHighlighter::~SyntaxHighlighter()
{

}
