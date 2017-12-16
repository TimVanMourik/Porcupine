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

#include <iostream>

#include <QDebug>
#include <QJsonArray>
#include <QPainter>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QScrollBar>
#include <QTimer>

#include "Link.hpp"
#include "Node.hpp"
#include "NodeEditor.hpp"
#include "NodeTreeEditor.hpp"
#include "Port.hpp"
#include "PostIt.hpp"
#include "Preferences.hpp"
//#include "SelectionBox.hpp"

NodeEditor::NodeEditor(
        QWidget* _parent
        ) :
    QGraphicsView(_parent),
    m_newLink(0),
    m_scalingFactor(1),
    m_lastClickedPoint(QPointF(0, 0)),
    m_fileName(QString()),
//    m_newSelection(0),
    m_treeModel(0),
    m_scrollTimerActive(false),
    m_scrollDelta(0)
{
    /// @todo when pressed 'backspace' in file name label, last clicked node is deleted #fix
    /// @todo info 'tooltip' options
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void NodeEditor::install(
        )
{
    Preferences& preferences = Preferences::getInstance();
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setBackgroundBrush(preferences.m_sceneBackgroundBrush);

    ///@todo the setScene command causes the window to be very small on startup
    setScene(scene);
    //makes sure that all events from the scene are passed on to the editor
    scene->installEventFilter(this);
//    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    show();
}

const QString& NodeEditor::getFileName(
        )
{
    return m_fileName;
}

void NodeEditor::setFileName(
        const QString& _fileName
        )
{
    m_fileName = _fileName;
}

void NodeEditor::printScene(
        QPainter& _painter
        )
{
    scene()->render(&_painter);
}

bool NodeEditor::eventFilter(
        QObject* _object,
        QEvent* _event
        )
{
    QGraphicsSceneMouseEvent* mouseEvent = (QGraphicsSceneMouseEvent*) _event;

    switch((int) _event->type())
    {
    case QEvent::GraphicsSceneMousePress:
    {
        switch ((int) mouseEvent->button())
        {
        case Qt::LeftButton:
        {
            const QGraphicsItem* item = itemAt(mouseEvent->scenePos(), QSize(3, 3));
            if (!item)
            {
                m_lastClickedPoint = mouseEvent->scenePos();
            }
            else if (item->type() == Port::Type)
            {
                m_newLink = new Link(scene());

                Port* port = (Port*) item;
                if(port->getPortType() == Port::PortType::INPUT)
                {
                    m_newLink->setPortTo((Port*) item);
                }
                else if(port->getPortType() == Port::PortType::OUTPUT)
                {
                    m_newLink->setPortFrom((Port*) item);
                }
                else
                {
                    delete m_newLink;
                    break;
                }
                m_newLink->setPositionFrom(item->scenePos());
                m_newLink->setPositionTo(mouseEvent->scenePos());
                m_newLink->updatePath();
                return true;
            }
            break;
        }
        case Qt::RightButton:
        {
            const QGraphicsItem* item = itemAt(mouseEvent->scenePos(), QSize(3, 3));
            if(!item)
            {
//                m_newSelection = new SelectionBox(mouseEvent->scenePos(), scene());
//                m_newSelection->reshape(mouseEvent->scenePos());
            }
            break;
        }
        }
    }
    case QEvent::GraphicsSceneMouseMove:
    {
        if(itemAt(mouseEvent->scenePos(), QSize(3, 3)))
        {
            setDragMode(QGraphicsView::NoDrag);
        }
        else
        {
            setDragMode(QGraphicsView::ScrollHandDrag);
        }
        if (m_newLink)
        {
            m_newLink->setPositionTo(mouseEvent->scenePos());
            m_newLink->updatePath();
            return true;
        }
        break;
    }
    case QEvent::GraphicsSceneMouseRelease:
    {
        if (m_newLink && mouseEvent->button() == Qt::LeftButton)
        {
            const QGraphicsItem* item = itemAt(mouseEvent->scenePos(), QSize(3, 3));
            if (item && item->type() == Port::Type)
            {
                Port* portCreated = (Port*) item;
                Port* portExisting;
                bool startAtBeginning;
                if(m_newLink->getPortFrom() == 0)
                {
                    startAtBeginning = false;
                    portExisting = m_newLink->getPortTo();
                }
                else //if(m_newLink->getPortTo() == 0)
                {
                    startAtBeginning = true;
                    portExisting = m_newLink->getPortFrom();
                }

                if (portCreated->getNode() != portExisting->getNode() && //Make sure the from and to nodes are not the same
                        portCreated->getPortType() != portExisting->getPortType() && //And both ports are not of the same type
                        !portCreated->isConnectedTo(portExisting)) //And the nodes are not already connected
                {
                    if(startAtBeginning)
                    {
                        if(!portExisting->getNode()->hasAncestor(portCreated->getNode()))
                        {
                            m_newLink->setPortTo(portCreated);
                        }
                        else
                        {
                            ///@todo Give a message that circularity is not appreciated
//                            std::cerr << "Sorry, no can do\n";
                            delete m_newLink;
                            m_newLink = 0;
                            return true;
                        }
                    }
                    else
                    {
                        if(!portCreated->getNode()->hasAncestor(portExisting->getNode()))
                        {
                            m_newLink->setPortFrom(portCreated);
                        }
                        else
                        {
                            ///@todo Give a message that circularity is not appreciated
//                            std::cerr << "Sorry, no can do\n";
                            delete m_newLink;
                            m_newLink = 0;
                            return true;
                        }
                    }
                    m_newLink->setPositionTo(portCreated->scenePos());
                    m_newLink->updatePath();
                    portCreated->addConnection(m_newLink);
                    portExisting->addConnection(m_newLink);

//                    if(m_newLink->getPortFrom()->hasFileName())
//                    {
//                        m_newLink->getPortTo()->fileNameChanged(m_newLink->getPortFrom()->getFileName(), true);
//                    }
//                    else if(m_newLink->getPortTo()->hasFileName())
//                    {
//                        m_newLink->getPortFrom()->fileNameChanged(m_newLink->getPortTo()->getFileName(), true);
//                    }
                    emit linkCreated(m_newLink->getPortFrom()->getNode(), m_newLink->getPortTo()->getNode());

                    m_newLink = 0;
                    return true;
                }
            }

            delete m_newLink;
            m_newLink = 0;
            return true;
        }
        break;
    }
    }
    viewport()->update();
    return QObject::eventFilter(_object, _event);
}

void NodeEditor::wheelEvent(
        QWheelEvent* _event
        )
{
    // When a wheelEvent is fired, a single-shot timer is created and delta values accumalated
    // from all wheelEvents fired during that timer. When the timer is not active, the scroll is
    // performed using the accumalated delta value. This is a temporary fix until QTBug-226 is fixed.
    this->m_scrollDelta += _event->delta();
    if (!m_scrollTimerActive) {
        float scalingStep = 0.9;
        if(this->m_scrollDelta < 0)
        {
            this->scale(scalingStep, scalingStep);
            m_scalingFactor *= scalingStep;
        }
        else
        {
            this->scale(1 / scalingStep, 1 / scalingStep);
            m_scalingFactor /= scalingStep;
        }

        this->m_scrollDelta = 0;
        this->m_scrollTimerActive = true;
        QTimer::singleShot(23, this, [=]() {
            this->m_scrollTimerActive = false;
        });
    }
    /// @todo pass on to selections
//    foreach (SelectionBox* selection, m_selections)
//    {
//        selection->updateOpacity(m_scalingFactor);
//    }
}

void NodeEditor::keyPressEvent(
        QKeyEvent* _event
        )
{
    QGraphicsView::keyPressEvent(_event);
    switch (_event->key())
    {
    case Qt::Key_Delete:
    {
        foreach (QGraphicsItem* item, scene()->items())
        {
            if(item->isSelected())
            {
                if(item->type() == Node::Type)
                {
                    //remove node from list view
                    if(m_treeModel)
                    {
                        m_treeModel->removeNode((const Node*) item);
                    }
                }
//                else if(item->type() == SelectionBox::Type)
//                {
//                    m_selections.removeOne((SelectionBox*)item);
//                }
                delete item;
                //if no break, program may crash when second deleted item was already deletted by first on cascade
                break;
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

const QGraphicsItem* NodeEditor::itemAt(
        const QPointF& _centrePosition,
        const QSize& _size
        )
{
    //Draw a square around the input position and return the item
    QList<QGraphicsItem*> itemsWithinSquare = scene()->items(QRectF(_centrePosition - QPointF(_size.width() / 2, _size.height()), _size));

    foreach(const QGraphicsItem* eachItem, itemsWithinSquare)
    {
        if (eachItem->type() > QGraphicsItem::UserType)
        {
            return eachItem;
        }
    }
    return 0;
}

void NodeEditor::saveToJson(
        QJsonObject& o_json
        )
{
    saveLinksToJson(o_json);
    savePostItsToJson(o_json);
    int x1, y1, x2, y2;
    geometry().getCoords(&x1, &y1, &x2, &y2);
    QJsonArray size;
    size.append(x1); size.append(y1); size.append(x2); size.append(y2);
    o_json["size"] = size;
}

void NodeEditor::saveLinksToJson(
        QJsonObject& o_json
        )
{
    QJsonArray links;
    foreach(QGraphicsItem* item, scene()->items())
    {
        if (item->type() == Link::Type)
        {
            QJsonObject linkObject;
            ((Link*) item)->saveToJson(linkObject);
            links << linkObject;
        }
    }
    o_json["links"] = links;
}

void NodeEditor::savePostItsToJson(
        QJsonObject& o_json
        )
{
    QJsonArray postIts;
    foreach(QGraphicsItem* item, scene()->items())
    {
        if (item->type() == PostIt::Type)
        {
            QJsonObject postItObject;
            ((PostIt*) item)->saveToJson(postItObject);
            postIts << postItObject;
        }
    }
    o_json["post-its"] = postIts;
}

void NodeEditor::loadFromJson(
        const QJsonObject& _json
        )
{
    scene()->clear();
    int x1, y1, x2, y2;
    QJsonArray size = _json["size"].toArray();
    x1 = size.at(0).toInt(0); y1 = size.at(1).toInt(0); x2 = size.at(2).toInt(0); y2 = size.at(3).toInt(0);
    setGeometry(x1, y1, x2, y2);

    QMap<quint64, Port*> portMap;
//    qDebug() << "Loading nodes";
    foreach (QJsonValue nodeValue, _json["nodes"].toArray())
    {
        Node* node = new Node(this);
        node->loadFromJson(nodeValue.toObject(), portMap);
        getTreeModel()->addNode(node);
    }
//    qDebug() << "Loading links";
    foreach (QJsonValue linkValue, _json["links"].toArray())
    {
        Link* link = new Link(scene());
        link->loadFromJson(linkValue.toObject(), portMap);
    }
//    qDebug() << "Loading post-its";
    foreach (QJsonValue postitValue, _json["post-its"].toArray())
    {
        PostIt* postit = new PostIt(this);
        postit->loadFromJson(postitValue.toObject());
    }
}

void NodeEditor::setTreeModel(
        NodeTreeEditor* _treeModel
        )
{
    m_treeModel = _treeModel;
    connect(this, SIGNAL(linkCreated(const Node*, const Node*)), m_treeModel, SLOT(linkCreated(const Node*, const Node*)));
}

NodeTreeEditor* NodeEditor::getTreeModel(
        ) const
{
    return m_treeModel;
}

Node* NodeEditor::addNode(
        const QJsonObject& _object
        )
{
    Node* node = new Node(this, _object);
    node->setPos(m_lastClickedPoint);
    if(m_treeModel)
    {
        m_treeModel->addNode(node);
    }
    return node;
}

Node* NodeEditor::addNode(
        const NodeSetting* _setting
        )
{
    Node* node = new Node(this, _setting);
    node->setPos(m_lastClickedPoint);
    if(m_treeModel)
    {
        m_treeModel->addNode(node);
    }
    return node;
}

PostIt* NodeEditor::addPostit(
        )
{
    PostIt* postIt = new PostIt(this);
    postIt->setPos(m_lastClickedPoint);
    return postIt;
}

QVector<const Link*> NodeEditor::getLinks(
        ) const
{
    QVector<const Link*> links(0);
    foreach(QGraphicsItem* item, scene()->items())
    {
        if (item->type() == Link::Type)
        {
            links.append((Link*) item);
        }
    }
    return links;
}

void NodeEditor::updateJson(
        )
{
    foreach (QGraphicsItem* item, scene()->items())
    {
        if(item->type() == Node::Type)
        {
            ((Node*) item)->updateJson();
        }
    }
}

const QJsonObject NodeEditor::getSelection(
        bool _destroyOnSelection
        ) const
{
    foreach (QGraphicsItem* item, scene()->items())
    {
        if(item->isSelected() && item->type() == Node::Type)
        {
            ((Node*) item)->updateJson();
            const QJsonObject selection = ((Node*) item)->toJson();
            if(_destroyOnSelection)
            {
                m_treeModel->removeNode((Node*) item);
                delete item;
            }
            return selection;
        }
    }
    return QJsonObject();
}

NodeEditor::~NodeEditor(
        )
{
    //For the weird instance that there is one and the editor is destroyed:
    delete m_newLink;
//    delete m_newSelection;
//    foreach (SelectionBox* selection, m_selections)
//    {
//        delete selection;
//    }
    delete scene();
}
