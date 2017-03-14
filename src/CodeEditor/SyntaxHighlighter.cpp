/*  Copyright (C) Tim van Mourik, 2014-2016
    Copyright (C) Tim van Mourik, 2017, DCCN
    All rights reserved

 This file is part of the Porcupine pipeline tool, see
 https://github.com/TimVanMourik/Porcupine for the documentation and
 details.

    This toolbox is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the fmri analysis toolbox. If not, see
    <http://www.gnu.org/licenses/>.
*/

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
