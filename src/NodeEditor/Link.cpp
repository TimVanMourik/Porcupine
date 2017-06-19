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

#include <assert.h>

#include <QJsonObject>
#include <QGraphicsScene>
#include <QPainter>

#include "Link.hpp"
#include "Port.hpp"
#include "Preferences.hpp"

Link::Link(
        QGraphicsScene* _scene
        ) :
    m_portFrom(0),
    m_portTo(0)
{
    _scene->addItem(this);
    setPen(QPen(QColor(110, 170, 110), 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void Link::setPositionFrom(
        const QPointF& _p
        )
{
    m_positionFrom = _p;
}

void Link::setPositionTo(
        const QPointF& _p
        )
{
    m_positionTo = _p;
}

void Link::setPortFrom(
        Port* _p
        )
{
    m_portFrom = _p;
//    m_portFrom->addConnection(this);
}

void Link::setPortTo(
        Port* _p
        )
{
    m_portTo = _p;
//    m_portTo->addConnection(this);
}

Port* Link::getPortFrom(
        ) const
{
    return m_portFrom;
}

Port* Link::getPortTo(
        ) const
{
    return m_portTo;
}

void Link::paint(
        QPainter* _painter,
        const QStyleOptionGraphicsItem* _option,
        QWidget* _widget
        )
{
    Q_UNUSED(_option);
    Q_UNUSED(_widget);

    Preferences& preferences = Preferences::getInstance();
    if(isSelected())
    {
        _painter->setPen(preferences.m_linkPenSelected);
        _painter->setBrush(preferences.m_linkBrushSelected);
    }
    else
    {
        _painter->setPen(preferences.m_linkPenUnselected);
        _painter->setBrush(preferences.m_linkBrushUnselected);
    }
    _painter->drawPath(path());
}

void Link::updatePath(
        )
{
    QPainterPath p;

    p.moveTo(m_positionFrom);

    qreal dx = m_positionTo.x() - m_positionFrom.x();
    qreal dy = m_positionTo.y() - m_positionFrom.y();

    QPointF controlPoint1(m_positionFrom.x() + dx * 0.5, m_positionFrom.y() + dy * 0.1);
    QPointF controlPoint2(m_positionFrom.x() + dx * 0.5, m_positionFrom.y() + dy * 0.9);

    p.cubicTo(controlPoint1, controlPoint2, m_positionTo);

    setPath(p);
}

void Link::setPositionFromPorts(
        )
{
    m_positionFrom = m_portFrom->scenePos();
    m_positionTo   = m_portTo->scenePos();
}

int Link::type(
        ) const
{
    return Type;
}

void Link::saveToJson(
        QJsonObject& o_json
        )
{
    o_json["from"] = QString::number((quint64) m_portFrom, 16);
    o_json["to"]   = QString::number((quint64) m_portTo,   16);
}

void Link::loadFromJson(
        const QJsonObject& _json,
        QMap<quint64, Port*>& _portMap
        )
{
    quint64 pointerFrom = (quint64) _json["from"].toString().toULongLong(0, 16);
    quint64 pointerTo   = (quint64) _json["to"  ].toString().toULongLong(0, 16);
    assert(pointerFrom != 0);
    assert(pointerTo   != 0);

    Port* p;
    p = _portMap[pointerFrom];
    setPortFrom(p);
    p = _portMap[pointerTo];
    setPortTo(p);

    _portMap[pointerFrom]->addConnection(this);
    _portMap[pointerTo  ]->addConnection(this);
    setPositionFromPorts();
    updatePath();
}

Port* Link::otherPort(
        const Port* _port
        )
{
    if(_port == m_portFrom)
    {
        return m_portTo;
    }
    else if(_port == m_portTo)
    {
        return m_portFrom;
    }
    else
    {
        return 0;
    }
}

Link::~Link()
{
    if(m_portFrom)
    {
        m_portFrom->removeLink(this);
    }
    if(m_portTo)
    {
        m_portTo->removeLink(this);
    }
}

