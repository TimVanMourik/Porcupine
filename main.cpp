/* Copyright (c) 2014, Tim van Mourik
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

    return app.exec();
}
