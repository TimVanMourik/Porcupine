/*
 * Copyright (C) 2014 Tim van Mourik
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

#include "NodeTreeModel.hpp"

class Link;
class QGraphicsScene;
class QKeyEvent;
class QDomDocument;
class NodeSetting;

class NodeEditor : public QGraphicsView
{
public:
    //
    explicit NodeEditor(
            QWidget* _parent = 0
            );
    //
    void install(
//            QGraphicsScene* _scene = 0
            );
    //
    bool eventFilter(
            QObject* _object,
            QEvent* _event
            );
    //
    void keyPressEvent(
            QKeyEvent* _event
            );
    //
    QGraphicsScene* getScene(
            ) const;
    //
    void save(
            QDataStream& _dataStream
            );
    //
    void saveToXml(
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
    void setTreeModel(
            NodeTreeModel* _treeModel
            );
    //
    NodeTreeModel* getTreeModel(
            ) const;
    //
    Node* addNode(
            NodeSetting* _setting = 0
            );
    //
    ~NodeEditor(
            );
private:
    //
    QGraphicsItem* itemAt(
            const QPointF& _position
            );
    //New link is created such that it always goes from an output port to an input port
    Link* m_newLink;
    //
    NodeTreeModel* m_treeModel;
};

#endif // NODEEDITOR_HPP
