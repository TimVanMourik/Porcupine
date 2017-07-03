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

#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QGraphicsPathItem>
#include <QPoint>
#include <QStandardItem>
#include <QFrame>

class Node;
class NodeSetting;
class PortBlock;
class PortPair;
class QDomDocument;
class QDomElement;
class QLabel;
class QLineEdit;
class QVBoxLayout;

#include "Hider.hpp"

#include <QPushButton>
class NodeTreeItem : public QFrame
{
    Q_OBJECT
public:
    ///@todo make sure that the item doesn't flash before moving to the right position
    NodeTreeItem(
            const Node* _node,
            QWidget* _parent
            );
    //
    void setPort(
            PortPair* _port
            );
    //
    bool isAncestorOf(
            NodeTreeItem* _item
            );
    //
    void saveToJson(
            QJsonObject& o_json
            ) const;
    //
    const Node* getNode(
            ) const;
    //
    const QJsonObject& getJson(
            ) const;
    //
    const QVector<PortPair*> getPorts(
            ) const;
    //
//    const NodeSetting* getNodeSetting(
//            ) const;
    //
    QVector<const Node*> getDescendants(
            );
    //
    void setNumber(
            unsigned int _i
            );
    //
    QString getParameterName(
            const QString& _portName
            ) const;
    //
    void mousePressEvent(
            QMouseEvent* _event
            );
    //
    void mouseMoveEvent(
            QMouseEvent* _event
            );
    //
    void mouseReleaseEvent(
            QMouseEvent* _event
            );
    //
    virtual ~NodeTreeItem(
            );
public slots:
    //
    void setSelected(
            bool _isSelected
            );
    //
    void addPort(
            );
signals:
    void moved(
            NodeTreeItem* _item
            );
private:
    //
    const Node* m_node;
    //
    QPoint m_startPosition;
    //
    QLabel* m_numberLabel;
    //
    unsigned int m_number;
    //
    bool m_isSelected;
    //
    PortBlock* m_portBlockLayout;
};

#endif // NODETREEITEM_H
