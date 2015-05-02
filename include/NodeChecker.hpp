#ifndef XMLSYNTAXHIGHLIGHTER_H
#define XMLSYNTAXHIGHLIGHTER_H


class NodeChecker : public QSyntaxHighlighter
{
    public:
        XmlSyntaxHighlighter(QTextDocument *parent = 0);

    protected:
        virtual void highlightBlock(const QString &text);

    private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;

        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat tagFormat;
        QTextCharFormat attributeFormat;
        QTextCharFormat attributeContentFormat;
        QTextCharFormat commentFormat;
};

#endif
