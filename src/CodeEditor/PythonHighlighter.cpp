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

