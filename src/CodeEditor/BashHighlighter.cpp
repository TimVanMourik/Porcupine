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

