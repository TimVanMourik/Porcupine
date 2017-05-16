/*  Copyright (C) Tim van Mourik, 2014-2017
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

#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <QList>
#include <QString>

#include "NodeSetting.hpp"
#include "NodeTreeItem.hpp"

class CodeEditor;
class Link;

class CodeGenerator
{
public:
    //
    CodeGenerator(
            CodeEditor* _editor = 0
            );
    //
    virtual QString generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList = QVector<const Link*>(0)
            ) = 0;
    //
    ~CodeGenerator();
protected:
    //
    CodeEditor* m_editor;
};

#endif // CODEGENERATOR_HPP
