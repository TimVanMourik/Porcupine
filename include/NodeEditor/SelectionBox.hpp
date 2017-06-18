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

#ifndef SELECTIONBOX_HPP
#define SELECTIONBOX_HPP

#include <QGraphicsPathItem>

class QDomElement;

class Node;
class Port;

class SelectionBox : public QGraphicsPathItem
{
public:
    //
    enum {
        Type = QGraphicsItem::UserType + 5
    };
    SelectionBox(
            const QPointF& _mousePosition,
            QGraphicsScene* _scene
            );
    //
    void paint(
            QPainter* _painter,
            const QStyleOptionGraphicsItem* _option,
            QWidget* _widget
            );
    //
    int type(
            ) const;
    //
    void reshape(
            const QPointF& _mousePosition
            );
    //
    void reshape(
            const qreal _x1,
            const qreal _y1,
            const qreal _x2,
            const qreal _y2
            );
    //
    void updateOpacity(
            float _scalingFactor
            );
    //
    void setNodeList(
            QList<Node*>& _nodeList
            );
    //
//    void saveToXml(
//            QDomElement& _xmlElement
//            );
    //
    void loadFromXml(
            QDomElement& _xmlNode,
            QMap<quint64, Port*>& o_portMap
            );
    //
    ~SelectionBox(
            );
private:
    //
    static qreal s_rounding;
    //
    QPointF m_topLeftCorner;
    //
    QList<Node*> m_nodeList;
};

#endif // SELECTIONBOX_HPP
