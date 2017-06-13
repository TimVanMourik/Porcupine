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

#ifndef NODEEDITOR_HPP
#define NODEEDITOR_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file NodeEditor.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QGraphicsView>

class Link;
//class SelectionBox;
class QGraphicsScene;
class QKeyEvent;
class QDomDocument;
class QDomElement;
class Node;
class NodeSetting;
class NodeTreeEditor;
class PostIt;

class NodeEditor : public QGraphicsView
{
    Q_OBJECT
public:
    //
    explicit NodeEditor(
            QWidget* _parent = 0
            );
    //
    void install(
            );
    //
    bool eventFilter(
            QObject* _object,
            QEvent* _event
            );
    //
    void wheelEvent(
            QWheelEvent* _event
            );
    //
    void keyPressEvent(
            QKeyEvent* _event
            );
    //
    void saveLinksToXml(
            QDomElement& _xmlFile
            );
    //
    void load(
            QDataStream& _dataStream
            );
    //
    void loadFromXml(
            QDomDocument& _xmlFile
            );
    //
    void printScene(
            QPainter& _painter
            );
    //
    void setTreeModel(
            NodeTreeEditor* _treeModel
            );
    //
    NodeTreeEditor* getTreeModel(
            ) const;
    //
    Node* addNode(
            const NodeSetting* _setting = 0
            );
    //
    PostIt* addPostit(
            );
    //
    QVector<const Link*> getLinks(
            ) const;
    //
    ~NodeEditor(
            );
signals:
    void linkCreated(
            const Node* _from,
            const Node* _to
            );
private:
    //
    const QGraphicsItem* itemAt(
            const QPointF& _centrePosition,
            const QSize& _size
            );
    //New link is created such that it always goes from an output port to an input port
    Link* m_newLink;
    //
    float m_scalingFactor;
    //
    QPointF m_lastClickedPoint;
    //
//    SelectionBox* m_newSelection;
    //
//    QList<SelectionBox*> m_selections;
    //
    NodeTreeEditor* m_treeModel;
};

#endif // NODEEDITOR_HPP
