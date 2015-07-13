#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    //
    SyntaxHighlighter(
            QTextDocument* parent = 0
            );
    //
    ~SyntaxHighlighter(
            );
protected:
    //
    void addHighlightRule(
            const QRegExp& _expression,
            const QTextCharFormat& _format
            );
private:
    //
    void highlightBlock(
            const QString& _text
            ) Q_DECL_OVERRIDE;

    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> m_highlightingRules;
};

#endif // SYNTAXHIGHLIGHTER_H
