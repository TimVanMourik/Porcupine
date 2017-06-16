
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

#include <assert.h>
#include <iostream>

#include <QApplication>
#include <QBoxLayout>
#include <QContextMenuEvent>
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QPainter>
#include <QPrinter>
#include <QPushButton>
#include <QSlider>
#include <QSplitter>
#include <QTabWidget>

#include "CodeEditor.hpp"
#include "MainWindow.hpp"
#include "NodeEditor.hpp"
#include "NodeTreeEditor.hpp"
#include "NodeLibrary.hpp"
#include "ParameterEditor.hpp"

MainWindow::MainWindow(
        QWidget* _parent
        ) :
    QMainWindow(_parent),
    m_nodeEditorWidget(new QTabWidget()),
    m_nodeTreeWidget  (new QWidget()),
    m_codeEditorWidget(new QWidget()),
    m_parameterWidget (new QWidget()),
    m_nodeEditors(0),
    m_nodeTreeEditors(0),
    m_codeEditors(0),
    m_parameterEditors(0),
    m_currentFileIndex(0)
{
    //Create an instance of the NodeLibrary
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    Q_UNUSED(nodeLibrary);

    // these widgets have to have a layout
    new QVBoxLayout(m_nodeTreeWidget);
    new QVBoxLayout(m_codeEditorWidget);
    new QVBoxLayout(m_parameterWidget);

    //Make the MainWindow and its layout for the central widget
    QSplitter* mainWidget = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(mainWidget);

    //Add the panels to the layout
    mainWidget->addWidget(m_nodeTreeWidget);
    QSplitter* rightWidget = new QSplitter(Qt::Vertical, mainWidget);

    QSplitter* nodeEditor = new QSplitter(Qt::Horizontal, rightWidget);
    nodeEditor->addWidget(m_nodeEditorWidget);
    nodeEditor->addWidget(m_parameterWidget);

    QWidget* codeEditor = new QWidget();
    QHBoxLayout* codeLayout = new QHBoxLayout(codeEditor);
    QPushButton* button = new QPushButton("Generate code");
    codeLayout->addWidget(button);
    codeLayout->addWidget(m_codeEditorWidget);

    rightWidget->addWidget(codeEditor);

    ///@todo stretch factors are a bit weird. Find out how to do this nicely
    nodeEditor->setStretchFactor(0, 10);
    nodeEditor->setStretchFactor(1, 1);

    createActions();
    createMenus();

//    loadDataTypes();
    loadDefaultNodes();

    connect(button, SIGNAL(released()), this, SLOT(nodeToCode()));
    connect(m_nodeEditorWidget, SIGNAL(currentChanged(int)), this, SLOT(setFileAt(int)));

    newFile();
}

void MainWindow::nodeToCode(
        )
{
    m_nodeTreeEditors[m_currentFileIndex]->generateCode();
    QVector<const Link*> allLinks = m_nodeEditors[m_currentFileIndex]->getLinks();
    m_codeEditors[m_currentFileIndex]->generateCode(m_nodeTreeEditors[m_currentFileIndex]->getNodeList(), allLinks);
}

void MainWindow::contextMenuEvent(
        QContextMenuEvent* _event
        )
{
    Q_UNUSED(_event);
//    QMenu menu(this);
//    menu.addAction(m_cutAct);
//    menu.addAction(m_copyAct);
//    menu.addAction(m_pasteAct);
//    menu.exec(_event->globalPos());
}

void MainWindow::keyPressEvent(
        QKeyEvent* _event
        )
{
    Q_UNUSED(_event);
}

void MainWindow::loadDefaultNodes(
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();

    QStringList toolboxNames;
    toolboxNames << QString(":/dictionaries/TvM/dict_%1.JSON");
    toolboxNames << QString(":/dictionaries/NiPype/dict_%1.JSON");
    unsigned int framePadding = 3;
    foreach (QString toolbox, toolboxNames)
    {
        unsigned int i = 0;
        while(true)
        {
            QFile xmlNodefile(toolbox.arg(i, framePadding, 10, QLatin1Char('0')));
            if(xmlNodefile.exists())
            {
                QStringList newNodes = nodeLibrary.addNodeSetting(xmlNodefile);
                if(!newNodes.isEmpty())
                {
                    updateNodeMenu(newNodes);
                }
            }
            else
            {
                break;
            }
            ++i;
        }
    }
}

void MainWindow::loadNewNodes(
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    QStringList fileNames = QFileDialog::getOpenFileNames();
    foreach(QString name, fileNames)
    {
        QFile file(name);
        QStringList newNodes = nodeLibrary.addNodeSetting(file);
        updateNodeMenu(newNodes);
    }
}

void MainWindow::updateNodeMenu(
        const QStringList& _nodes
        )
{
    assert(!_nodes.isEmpty());
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    foreach (QString node, _nodes)
    {
        const QStringList category = nodeLibrary.getCategory(node);
        QAction* newAction = new QAction(node, this);
        newAction->setData(node);

        int categoryNumber = 0;
        QMenu* currentMenu = m_nodesMenu;
        while(categoryNumber < category.length())
        {
            QList<QMenu*> menus = currentMenu->findChildren<QMenu*>(QString(), Qt::FindDirectChildrenOnly);
            bool menuFound = false;
            foreach (QMenu* menu, menus)
            {
                if(menu->title().compare(category[categoryNumber]) == 0)
                {
                    currentMenu = menu;
                    menuFound = true;
                    break;
                }
            }
            if(!menuFound)
            {
                QMenu* newMenu = new QMenu(category[categoryNumber], currentMenu);
                currentMenu->addMenu(newMenu);
                currentMenu = newMenu;
            }
            ++categoryNumber;
        }
        currentMenu->addAction(newAction);
    }
}

void MainWindow::nodeSlot(
        QAction* _action
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    QString nodeType = _action->data().toString();
    const NodeSetting* setting = nodeLibrary.getNodeSetting(nodeType);
    addNode(setting);
}

void MainWindow::saveFileToXml()
{
    QString fileName = QFileDialog::getSaveFileName();
    if (fileName.isEmpty())
    {
        return;
    }
    QDomDocument xmlFile;
    QDomProcessingInstruction xmlProcessingInstruction = xmlFile.createProcessingInstruction("xml", "version=\"1.0\"");
    xmlFile.appendChild(xmlProcessingInstruction);

    QDomElement root = xmlFile.createElement("pipeline");
    xmlFile.appendChild(root);

    //save all nodes
    m_nodeTreeEditors[m_nodeEditorWidget->currentIndex()]->saveToXml(root);
    //save all links
    m_nodeEditors[m_nodeEditorWidget->currentIndex()]->saveLinksToXml(root);

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << xmlFile.toString();
    }
    file.close();
}

void MainWindow::openFile()
{
    QDomDocument document;
    #ifdef DARWIN // on Mac, the file dialog does not want to close with the native file dialog
        QFile file(QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Pipelines (*.pipe)"), 0, QFileDialog::DontUseNativeDialog));
    #else
        QFile file(QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Pipelines (*.pipe)"), 0));
    #endif
    QFileInfo fileInfo(file.fileName());
    QString filename(fileInfo.fileName());
    QCoreApplication::processEvents();
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cerr << "Error: cannot open file\n";
        return;
    }
    if (!document.setContent(&file))
    {
        std::cerr << "Error: cannot read file\n";
        file.close();
        return;
    }
    file.close();

    ///@todo if the file is empty, use it. Otherwise, create a new tab
//    if(m_nodeEditors[m_tabLayout->currentIndex()]->children().length() != 0)
//    {
//        std::cerr << m_nodeEditors[m_tabLayout->currentIndex()]->children().length() << "\n";
    newFile();
//    }

    m_nodeEditorWidget->setTabText(m_nodeEditorWidget->currentIndex(), filename);
    m_nodeEditors[m_nodeEditorWidget->currentIndex()]->loadFromXml(document);
}

void MainWindow::printFile(
        )
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);

    QString fileName = QFileDialog::getSaveFileName();
    if (fileName.isEmpty())
    {
        qDebug() << "No file name was chosen. Ergo, no file will be saved.";
        return;
    }
    printer.setOutputFileName(fileName);

    QPainter painter;
    if(!painter.begin(&printer))
    {
        qDebug() << "Error setting up printer.";
        return;
    }
    painter.setRenderHint(QPainter::TextAntialiasing);
    m_nodeEditors[m_nodeEditorWidget->currentIndex()]->printScene(painter);
    painter.end();
}

void MainWindow::newFile(
        )
{
    //Create a node editor
    m_nodeEditors.append(       new NodeEditor(this));
    m_nodeTreeEditors.append(   new NodeTreeEditor(this));
    m_codeEditors.append(       new CodeEditor(this));
    m_parameterEditors.append(  new ParameterEditor(this));

    //Add it to a new tab
    m_currentFileIndex = m_nodeEditors.length() - 1;
    m_nodeEditorWidget->addTab(m_nodeEditors[m_currentFileIndex], tr("Untitled"));
    m_nodeTreeWidget    ->layout()->addWidget(m_nodeTreeEditors[m_currentFileIndex]);
    m_codeEditorWidget  ->layout()->addWidget(m_codeEditors[m_currentFileIndex]);
    m_parameterWidget   ->layout()->addWidget(m_parameterEditors[m_currentFileIndex]);

    m_nodeEditors[m_currentFileIndex]->setTreeModel(m_nodeTreeEditors[m_currentFileIndex]);
    m_nodeTreeEditors[m_currentFileIndex]->setCodeEditor(m_codeEditors[m_currentFileIndex]);
    m_codeEditors[m_currentFileIndex]->setParameterEditor(m_parameterEditors[m_currentFileIndex]);

    setFileAt(m_currentFileIndex);
    m_nodeEditors.last()->install();
}

void MainWindow::undoEdit(
        )
{
}

void MainWindow::redoEdit(
        )
{
}

void MainWindow::cutEdit(
        )
{
}

void MainWindow::copyEdit(
        )
{
}

void MainWindow::pasteEdit(
        )
{
}

void MainWindow::addNode(
        const NodeSetting* _setting
        )
{
    m_nodeEditors[m_currentFileIndex]->addNode(_setting);
}

void MainWindow::addPostIt(
        )
{
    m_nodeEditors[m_currentFileIndex]->addPostit();
}

void MainWindow::setFileAt(
        int _tabNumber
        )
{
    m_currentFileIndex = _tabNumber;
    m_nodeEditorWidget->setCurrentIndex(m_currentFileIndex);
    for (int i = 0; i < m_nodeTreeWidget->layout()->count(); ++i)
    {
        if(i == m_currentFileIndex)
        {
            m_nodeTreeWidget->layout()->itemAt(i)->widget()->setVisible(true);
            m_codeEditorWidget->layout()->itemAt(i)->widget()->setVisible(true);
            m_parameterWidget->layout()->itemAt(i)->widget()->setVisible(true);
        }
        else
        {
            m_nodeTreeWidget->layout()->itemAt(i)->widget()->setVisible(false);
            m_codeEditorWidget->layout()->itemAt(i)->widget()->setVisible(false);
            m_parameterWidget->layout()->itemAt(i)->widget()->setVisible(false);
        }
    }
}

void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("File"));
    m_fileMenu->addAction(m_newAct);
    m_fileMenu->addAction(m_openAct);
    /// @todo Add 'open recent file' to the menu
    m_fileMenu->addAction(m_saveToXmlAct);
    m_fileMenu->addAction(m_printAct);
    m_fileMenu->addAction(m_loadNodesAct);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAct);

    m_editMenu = menuBar()->addMenu(tr("Edit"));
    m_editMenu->addAction(m_undoAct);
    m_editMenu->addAction(m_redoAct);
    m_editMenu->addSeparator();
    m_editMenu->addAction(m_cutAct);
    m_editMenu->addAction(m_copyAct);
    m_editMenu->addAction(m_pasteAct);

    m_nodesMenu = menuBar()->addMenu(tr("Nodes"));

    m_postitMenu = menuBar()->addMenu(tr("Post-its"));
    m_postitMenu->addAction(m_postitAct);

    connect(m_nodesMenu, SIGNAL(triggered(QAction*)), this, SLOT(nodeSlot(QAction*)));
}

void MainWindow::createActions()
{
    m_newAct = new QAction(tr("New"), this);
    m_newAct->setShortcuts(QKeySequence::New);
    m_newAct->setStatusTip(tr("Create a new file"));
    connect(m_newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    m_openAct = new QAction(tr("Open..."), this);
    m_openAct->setShortcuts(QKeySequence::Open);
    m_openAct->setStatusTip(tr("Open an existing file"));
    connect(m_openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    m_saveToXmlAct = new QAction(tr("Save..."), this);
    m_saveToXmlAct->setShortcuts(QKeySequence::Save);
    m_saveToXmlAct->setStatusTip(tr("Save the document as XML-file to disk"));
    connect(m_saveToXmlAct, SIGNAL(triggered()), this, SLOT(saveFileToXml()));

    m_printAct = new QAction(tr("Print..."), this);
    m_printAct->setShortcuts(QKeySequence::Print);
    m_printAct->setStatusTip(tr("Print the document"));
    connect(m_printAct, SIGNAL(triggered()), this, SLOT(printFile()));

    m_loadNodesAct = new QAction(tr("Load Nodes..."), this);
//    m_loadNodesAct->setShortcuts(QKeySequence::);
    m_loadNodesAct->setStatusTip(tr("Load new nodes into the library"));
    connect(m_loadNodesAct, SIGNAL(triggered()), this, SLOT(loadNewNodes()));

    m_exitAct = new QAction(tr("Quit"), this);
    m_exitAct->setShortcuts(QKeySequence::Quit);
    m_exitAct->setStatusTip(tr("Quit the application"));
    connect(m_exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_undoAct = new QAction(tr("Undo"), this);
    m_undoAct->setShortcuts(QKeySequence::Undo);
    m_undoAct->setStatusTip(tr("Undo the last operation"));
    connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undoEdit()));

    m_redoAct = new QAction(tr("Redo"), this);
    m_redoAct->setShortcuts(QKeySequence::Redo);
    m_redoAct->setStatusTip(tr("Redo the last operation"));
    connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redoEdit()));

    m_cutAct = new QAction(tr("Cut"), this);
    m_cutAct->setShortcuts(QKeySequence::Cut);
    m_cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(m_cutAct, SIGNAL(triggered()), this, SLOT(cutEdit()));

    m_copyAct = new QAction(tr("Copy"), this);
    m_copyAct->setShortcuts(QKeySequence::Copy);
    m_copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(m_copyAct, SIGNAL(triggered()), this, SLOT(copyEdit()));

    m_pasteAct = new QAction(tr("Paste"), this);
    m_pasteAct->setShortcuts(QKeySequence::Paste);
    m_pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(m_pasteAct, SIGNAL(triggered()), this, SLOT(pasteEdit()));

    m_postitAct = new QAction(tr("Post-it"), this);
    connect(m_postitAct, SIGNAL(triggered()), this, SLOT(addPostIt()));
}

MainWindow::~MainWindow()
{
    foreach (CodeEditor* editor, m_codeEditors)
    {
        delete editor;
    }
    foreach (NodeTreeEditor* editor, m_nodeTreeEditors)
    {
        delete editor;
    }
    foreach (NodeEditor* editor, m_nodeEditors)
    {
        delete editor;
    }
    foreach (ParameterEditor* editor, m_parameterEditors)
    {
        delete editor;
    }
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    nodeLibrary.destroy();
}
