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

#include <QDomDocument>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

#include "Link.hpp"
#include "Preferences.hpp"
#include "Port.hpp"
#include "PortPair.hpp"

qreal Port::s_margin = 0;
qreal Port::s_radius = 4;

Port::Port(
        const Node* _node
        ) :
    QGraphicsPathItem((QGraphicsItem*)_node),
    m_node(_node),
    m_other(0),
    m_hasFileName(false)
{
    Preferences& preferences = Preferences::getInstance();
    QPainterPath portDrawing;
    qreal centreX   = -s_radius;
    qreal centreY   = -s_radius;
    qreal sizeX     = 2 * s_radius;
    qreal sizeY     = 2 * s_radius;
    portDrawing.addEllipse(centreX, centreY, sizeX, sizeY);
    setPath(portDrawing);

    setPen(preferences.m_portPenUnselected);
    setBrush(preferences.m_portBrushUnselected);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void Port::setPortPair(
        PortPair* _pair
        )
{
    m_pair = _pair;
}

void Port::setPortType(
        PortType _type
        )
{
    m_type = _type;
}

void Port::addConnection(
        Link* _newLink
        )
{
    m_connections.append(_newLink);
    m_pair->isConnected(true);
}

Port::PortType Port::getPortType(
        ) const
{
    return m_type;
}

PortPair* Port::getPortPair(
        ) const
{
    return m_pair;
}

bool Port::isConnectedTo(
        Port* _other
        )
{
    //For each connection
    foreach(Link* links, m_connections)
    {
        //check if the from or to port is the other one
        if(links->getPortFrom() == _other || links->getPortTo() == _other)
        {
            return true;
        }
    }
    return false;
}

QVariant Port::itemChange(
        GraphicsItemChange _change,
        const QVariant& _value
        )
{
    if (_change == ItemScenePositionHasChanged)
    {
        foreach(Link* eachLink, m_connections)
        {
            eachLink->setPositionFromPorts();
            eachLink->updatePath();
        }
    }
    return _value;
}

const Node* Port::getNode(
        ) const
{
    assert(m_node != 0);
    return m_node;
}

qreal Port::getRadius(
        )
{
    return s_radius;
}

const QVector<Link*>& Port::getConnections(
        ) const
{
    return m_connections;
}

QVector<Port*> Port::getConnectedPorts(
        ) const
{
    QVector<Port*> connectedPorts;
    foreach(Link* link, m_connections)
    {
        assert(link != 0);
        if(m_type == PortType::INPUT)
        {
            connectedPorts.append(link->getPortFrom());
        }
        else if(m_type == PortType::OUTPUT)
        {
            connectedPorts.append(link->getPortTo());
        }
    }
    return connectedPorts;
}

void Port::removeLink(
        Link* _link
        )
{
    m_connections.removeOne(_link);
    if(m_connections.length() == 0)
    {
        m_pair->isConnected(false);
    }
}

void Port::saveToXml(
        QDomElement& _xmlElement
        )
{
    QDomDocument xml;
    QDomElement port = xml.createElement("port");
    QString portType;
    if(getPortType() == Port::INPUT)
    {
        portType = "input";
    }
    else if(getPortType() == Port::OUTPUT)
    {
        portType = "output";
    }
    port.setAttribute("type", portType);
    port.setAttribute("identifier", QString::number((quint64) this, 16));
    _xmlElement.appendChild(port);
}

int Port::type(
        ) const
{
    return Type;
}

void Port::paint(
        QPainter* _painter,
        const QStyleOptionGraphicsItem* _option,
        QWidget* _widget
        )
{
    Q_UNUSED(_option);
    Q_UNUSED(_widget);

    Preferences& preferences = Preferences::getInstance();
    if(m_hasFileName)
    {
        _painter->setPen(preferences.m_portPenSelected);
        _painter->setBrush(preferences.m_portBrushSelected);

    }
    else
    {
        _painter->setPen(preferences.m_portPenUnselected);
        _painter->setBrush(preferences.m_portBrushUnselected);
    }
    _painter->drawPath(path());
}

void Port::setOther(
        Port* _other
        )
{
    m_other = _other;
}

bool Port::hasFileName(
        ) const
{
    return m_hasFileName;
}

void Port::setHasFileName(
        bool _bool
        )
{
    m_hasFileName = _bool;
    update();
}

void Port::fileNameChanged(
        const QString& _fileName,
        bool _cascadeUp
        )
{
    m_pair->fileNameChanged(_fileName, _cascadeUp);
}

const QString& Port::getFileName(
        ) const
{
    return m_pair->getFileName();
}

Port::~Port(
        )
{
    foreach(Link* link, m_connections)
    {
        delete link;
    }
}
