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

class Link;
class SelectionBox;
class QGraphicsScene;
class QKeyEvent;
class QDomDocument;
class QDomElement;
class Node;
class NodeSetting;
class NodeTreeEditor;

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
    SelectionBox* m_newSelection;
    //
//    QList<SelectionBox*> m_selections;
    //
    NodeTreeEditor* m_treeModel;
};

#endif // NODEEDITOR_HPP
