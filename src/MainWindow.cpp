/*
 * Copyright (C) 2014 Tim van Mourik
*/

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
#include <QPushButton>
#include <QTabWidget>
#include <QSplitter>
#include <QTabWidget>

#include "MainWindow.hpp"
#include "NodeEditor.hpp"
#include "NodeTreeEditor.hpp"
#include "NodeLibrary.hpp"

MainWindow::MainWindow(
        QWidget* parent
        ) :
    QMainWindow(parent),
    m_nodeEditorWidget(new QTabWidget(this)),
    m_nodeTreeWidget(new QWidget(this)),
    m_nodeEditors(0),
    m_nodeTreeEditors(0),
    m_currentFileIndex(0)
{
    //Create an instance of the NodeLibrary
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    Q_UNUSED(nodeLibrary);

    //
    new QVBoxLayout(m_nodeTreeWidget);
    new QVBoxLayout(m_nodeEditorWidget);

//    Make the MainWindow and its layout for the central widget
    QSplitter* layout = new QSplitter();
    setCentralWidget(layout);

    //Add the panels to the layout
    QWidget* widget = new QWidget();
    QVBoxLayout* leftSide = new QVBoxLayout();
    QPushButton* button = new QPushButton("Generate MATLAB code");
    leftSide->addWidget(m_nodeTreeWidget);
    leftSide->addWidget(button);
    widget->setLayout(leftSide);

    layout->addWidget(widget);
    layout->addWidget(m_nodeEditorWidget);
    ///@todo stretch factors are a bit weird. Find out how to do this nicely
    layout->setStretchFactor(0, 1);
    layout->setStretchFactor(1, 12);

    createActions();
    createMenus();

    loadDataTypes();
    loadNodes();

    newFile();

    connect(m_nodeEditorWidget, SIGNAL(currentChanged(int)), this, SLOT(setFileAt(int)));
}

//void MainWindow::contextMenuEvent(
//        QContextMenuEvent* _event
//        )
//{
//    QMenu menu(this);
//    menu.addAction(m_cutAct);
//    menu.addAction(m_copyAct);
//    menu.addAction(m_pasteAct);
//    menu.exec(_event->globalPos());
//}

void MainWindow::keyPressEvent(
        QKeyEvent* _event
        )
{
    Q_UNUSED(_event);
}

void MainWindow::loadDataTypes(
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    QFile schemaFile(QString(":/datatype_schema.xsd"));
    nodeLibrary.setDataTypeSchema(schemaFile);

    unsigned int i = 0;
    while(true)
    {
        QFile xmlTypefile(QString(":/Default/DataTypes/type_%1.xml").arg(i));
        if(xmlTypefile.exists())
        {
            nodeLibrary.addDataTypes(xmlTypefile);
        }
        else
        {
            break;
        }
        ++i;
    }
}

void MainWindow::loadNodes(
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    QFile schemaFile(QString(":/node_schema.xsd"));
    nodeLibrary.setNodeSchema(schemaFile);


    unsigned int i = 0;
    while(true)
    {
        QFile xmlNodefile(QString(":/Default/TVM/node_%1.xml").arg(i));
        if(xmlNodefile.exists())
        {
            nodeLibrary.addNodeSetting(xmlNodefile);
        }
        else
        {
//            std::cerr << "Break\n";
            break;
        }
//        std::cerr << "Node " << i << "\n";
        ++i;
    }

    updateNodeMenu();
}

void MainWindow::updateNodeMenu(
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    QStringList nodeNames = nodeLibrary.getNodeNames();
    for(int i = 0; i < nodeNames.size(); ++i)
    {
        //Replace by 'if node does not yet exist'
        if(true)
        {
            QAction* newAction = new QAction(nodeNames[i], this);
            newAction->setData(nodeNames[i]);

            m_nodesMenu->addAction(newAction);
        }
    }
    connect(m_nodesMenu, SIGNAL(triggered(QAction*)), this, SLOT(nodeSlot(QAction*)));
}

void MainWindow::nodeSlot(
        QAction* _action
        )
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    QString nodeType = _action->data().toString();
    NodeSetting* setting = nodeLibrary.getNodeSetting(nodeType);
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

    m_nodeEditors[m_nodeEditorWidget->currentIndex()]->saveToXml(root);

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
    QFile file(QFileDialog::getOpenFileName());
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

    m_nodeEditors[m_nodeEditorWidget->currentIndex()]->loadFromXml(document);
}

void MainWindow::printFile(
        )
{
}

void MainWindow::newFile(
        )
{
//    Preferences& preferences = Preferences::getInstance();

    //Create a node editor
    m_nodeEditors.append(new NodeEditor(this));
    m_nodeTreeEditors.append(new NodeTreeEditor());

    //Add it to a new tab
    m_currentFileIndex = m_nodeEditors.length() - 1;
    m_nodeEditorWidget->addTab(m_nodeEditors[m_currentFileIndex], tr("Untitled"));
    m_nodeTreeWidget->layout()->addWidget(m_nodeTreeEditors[m_currentFileIndex]);

    m_nodeEditors[m_currentFileIndex]->setTreeModel(m_nodeTreeEditors[m_currentFileIndex]);

    setFileAt(m_currentFileIndex);
    //Install an empty scene in the tab
//    QGraphicsScene* scene = new QGraphicsScene();
//    scene->setBackgroundBrush(preferences.getSceneBackgroundBrush());
    m_nodeEditors.last()->install(/*scene*/);
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
        NodeSetting* _setting
        )
{
    m_nodeEditors[m_currentFileIndex]->addNode(_setting);
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
        }
        else
        {
            m_nodeTreeWidget->layout()->itemAt(i)->widget()->setVisible(false);
        }
    }
}

void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("File"));
    m_fileMenu->addAction(m_newAct);
    m_fileMenu->addAction(m_openAct);
    m_fileMenu->addAction(m_saveToXmlAct);
    m_fileMenu->addAction(m_printAct);
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
}

MainWindow::~MainWindow()
{
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();
    nodeLibrary.destroy();
}
