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

