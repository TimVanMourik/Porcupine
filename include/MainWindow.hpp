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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//----------------------------------------------------------------------------------------------------------------------
/// @file MainWindow.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QJsonObject>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QSlider;

class CodeEditor;
class NodeEditor;
class NodeSetting;
class NodeTreeEditor;
class ParameterEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    //
    explicit MainWindow(
            QWidget* _parent = 0
            );
    //
    ~MainWindow(
            );

private slots:
    //
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
    void closeTab(
            int _index
            );
    //
//    void saveFileToXml(
//            );
    //
    void saveFileToJson(
            );

    void openFile(
            );
    void newFile(
            );
    void exportFile(
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
    void addNode(
            const QJsonObject& _object
            );
    void addPostIt(
            );
    void updateNodeMenu(
            const QStringList& _node
            );
public slots:
    //
    void nodeToCode(
            );
    //
    void saveCode(
            );
private:
    void createActions(
            );
    void createMenus(
            );
    void nodesMenu(
            );
//    void loadDataTypes(
//            );
    void loadDefaultNodes(
            );

    QTabWidget* m_nodeEditorWidget;
    QWidget* m_nodeTreeWidget;
    QWidget* m_codeEditorWidget;
    QWidget* m_parameterWidget;

    QVector<NodeEditor*> m_nodeEditors;
    QVector<NodeTreeEditor*> m_nodeTreeEditors;
    QVector<CodeEditor*> m_codeEditors;
    QVector<ParameterEditor*> m_parameterEditors;

    int m_currentFileIndex;

    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_nodesMenu;
    QMenu* m_postitMenu;

    QAction* m_newAct;
    QAction* m_openAct;
    QAction* m_saveToJsonAct;
    QAction* m_exportAct;
    QAction* m_loadNodesAct;
    QAction* m_exitAct;
    QAction* m_undoAct;
    QAction* m_redoAct;
    QAction* m_cutAct;
    QAction* m_copyAct;
    QAction* m_pasteAct;
    QAction* m_postitAct;

    QJsonObject m_clipboard;

    /// @brief
    QVector<QAction*> m_nodeActs;
};

#endif // MAINWINDOW_H
