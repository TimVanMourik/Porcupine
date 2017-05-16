
/* Copyright (C) Tim van Mourik, 2014-2016
 * Copyright (C) Tim van Mourik, 2017, DCCN
 * All rights reserved
 *
 * This program has been created from scratch, but was inspired by the following packages:
 *
 * Mipav, http://mipav.cit.nih.gov/
 * Loni Pipeline, http://pipeline.bmap.ucla.edu/
 * Taverna, http://www.taverna.org.uk/
 * Blender, http://www.blender.org/
 * Stanislaw Adaszewski's QNodesEditor, http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor
 * Open Assembler, http://openassembler.wordpress.com/
 * Kiwi, https://github.com/nical/kiwi
 * QT Node Editor, http://nukengine.com/qt-node-editor/
 * Lynx, http://safakoner.webfactional.com/rnd/tool/2/
 * Nipype, http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3159964/
 *
 * To my knowledge non of these ideas or examples are patented or need to be referenced explicitly in the way I have used them.
 */


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

#include "MainWindow.hpp"
#include <QApplication>

int main(
        int argc,
        char *argv[]
        )
{
    QApplication app(argc, argv);
    MainWindow w;
    w.showMaximized();
    w.setWindowTitle("PORcupine Creates Ur PipelINE  © Tim van Mourik");
    w.setWindowIcon(QIcon("porcupine.icns"));

    return app.exec();
}
