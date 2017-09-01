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

#ifndef LINK_HPP
#define LINK_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Link.hpp
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QGraphicsItem>
#include <QGraphicsPathItem>

class QDomElement;

class Port;

class Link : public QGraphicsPathItem
{
public:
    //
    enum {
        Type = QGraphicsItem::UserType + 1
    };
    //
    Link(
            QGraphicsScene* _scene = 0
            );
    //
    void setPositionFrom(
            const QPointF& _p
                 );
    //
    void setPositionTo(
            const QPointF& _p
            );
    //
    void setPortFrom(
            Port* _p
            );
    //
    void setPortTo(
            Port* _p
            );
    //
    Port* getPortFrom(
            ) const;
    //
    Port* getPortTo(
            ) const;
    //
    void updatePath(
            );
    //
    void setPositionFromPorts(
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
    void saveToJson(
            QJsonObject& o_json
            );
    //
    void loadFromJson(
            const QJsonObject& _json,
            QMap<quint64, Port*>& o_portMap
            );
    //
    Port* otherPort(
            const Port* _port
            );
    //
    ~Link(
            );
private:
    //
    QPointF m_positionFrom;
    //
    QPointF m_positionTo;
    //
    Port* m_portFrom;
    //
    Port* m_portTo;
};

#endif // LINK_HPP
