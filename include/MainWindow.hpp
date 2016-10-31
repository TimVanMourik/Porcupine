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

class QSlider;

class CodeEditor;
class NodeEditor;
class NodeSetting;
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
    void contextMenuEvent(
            QContextMenuEvent* _event
            );
    //
    void keyPressEvent(
            QKeyEvent* _event
            );
    //
    void setFileAt(
            int _tabNumber
            );
    //
    void nodeScaleSliderMoved(
            int _value
            );
    //
    void nodeScaleSliderReleased(
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
    void loadNewNodes(
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
            const NodeSetting* _setting = 0
            );
    void updateNodeMenu(
            const QString& _node
            );
public slots:
    //
    void nodeToCode(
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
    void loadDefaultNodes(
            );

    QTabWidget* m_nodeEditorWidget;
    /// @todo make sure that clicks and scrolls are handled appropriately
    QSlider* m_nodeScaleSlider;
    bool m_scaleReleased;
    float m_currentScale;
    QWidget* m_nodeTreeWidget;
    QWidget* m_codeEditorWidget;

    QVector<NodeEditor*> m_nodeEditors;
    QVector<NodeTreeEditor*> m_nodeTreeEditors;
    QVector<CodeEditor*> m_codeEditors;

    int m_currentFileIndex;

    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_nodesMenu;

    QAction* m_newAct;
    QAction* m_openAct;
    QAction* m_saveToXmlAct;
    QAction* m_printAct;
    QAction* m_loadNodesAct;
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
