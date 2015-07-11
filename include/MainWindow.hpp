/*
 * Copyright (C) 2014 Tim van Mourik
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//----------------------------------------------------------------------------------------------------------------------
/// @file MainWindow.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QMainWindow>
#include <QtXmlPatterns>

namespace Ui {
class MainWindow;
}

class NodeEditor;
class NodeSetting;
//class NodeListWidget;
class NodeTreeEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(
            QWidget* _parent = 0
            );
    ~MainWindow(
            );

private slots:
//    void contextMenuEvent(
//            QContextMenuEvent* _event
//            );
    //
    void keyPressEvent(
            QKeyEvent* _event
            );
    //
    void setFileAt(
            int _tabNumber
            );

    //
    void saveFileToXml(
            );
    void openFile(
            );
    void newFile(
            );
    void printFile(
            );
    void undoEdit(
            );
    void redoEdit(
            );
    void cutEdit(
            );
    void copyEdit(
            );
    void pasteEdit(
            );
    void nodeSlot(
            QAction* _action
            );
    void addNode(
            NodeSetting* _setting = 0
            );
    void updateNodeMenu(
            );
private:
    void createActions(
            );
    void createMenus(
            );
    void nodesMenu(
            );
    void loadDataTypes(
            );
    void loadNodes(
            );

    QTabWidget* m_nodeEditorWidget;
    QWidget* m_nodeTreeWidget;
    QVector<NodeEditor*> m_nodeEditors;
    QVector<NodeTreeEditor*> m_nodeTreeEditors;

    int m_currentFileIndex;

    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_nodesMenu;

    QAction* m_newAct;
    QAction* m_openAct;
    QAction* m_saveToXmlAct;
    QAction* m_printAct;
    QAction* m_exitAct;
    QAction* m_undoAct;
    QAction* m_redoAct;
    QAction* m_cutAct;
    QAction* m_copyAct;
    QAction* m_pasteAct;

    /// @brief
    QVector<QAction*> m_nodeActs;
    /// @brief
    QXmlSchemaValidator* m_nodeValidator;
};

#endif // MAINWINDOW_H
