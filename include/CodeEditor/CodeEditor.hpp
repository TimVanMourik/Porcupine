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

#ifndef CODEEDITOR_HPP
#define CODEEDITOR_HPP

#include <QTabWidget>

class CodeGenerator;
class Link;
class NodeTreeItem;
class QTextEdit;

class CodeEditor : public QTabWidget
{
public:
    //
    CodeEditor(
            QWidget* _parent = 0
            );
    //
    void generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            );
    //
    ~CodeEditor(
            );
private:
    //
    void setupMatlabEditor(
            );
    //
    void setupSpmEditor(
            );
    //
    void setupBashEditor(
            );
    //
    void setupPythonEditor(
            );
    //
    QMap<QString, QTextEdit*> m_textEditors;
    //
    QMap<QString, CodeGenerator*> m_codeGenerators;
    //
    QStringList m_programmingLanguages;
};

#endif // CODEEDITOR_HPP
