/*
 * Copyright (C) 2014 Tim van Mourik
*/

#include <QDomDocument>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

#include "Link.hpp"
#include "Port.hpp"

qreal Port::s_margin = 0;
qreal Port::s_radius = 4;

Port::Port(
        QGraphicsItem* _parent
        ) :
    QGraphicsPathItem(_parent),
    m_other(0),
    m_hasFileName(false)
{
    Preferences& preferences = Preferences::getInstance();
    setNode((Node*) _parent);
    QPainterPath portDrawing;
    qreal centreX   = -s_radius;
    qreal centreY   = -s_radius;
    qreal sizeX     = 2 * s_radius;
    qreal sizeY     = 2 * s_radius;
    portDrawing.addEllipse(centreX, centreY, sizeX, sizeY);
    setPath(portDrawing);

    setPen(preferences.getPortPenUnselected());
    setBrush(preferences.getPortBrushUnselected());

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void Port::setNode(
        Node* _node
        )
{
    m_node = _node;
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
}

Port::PortType Port::getPortType(
        ) const
{
    return m_type;
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

bool Port::removeLink(
        Link* _link
        )
{
    return m_connections.removeOne(_link);
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
        _painter->setPen(preferences.getPortPenSelected());
        _painter->setBrush(preferences.getPortBrushSelected());

    }
    else
    {
        _painter->setPen(preferences.getPortPenUnselected());
        _painter->setBrush(preferences.getPortBrushUnselected());
    }
    _painter->drawPath(path());
}

void Port::setOther(
        Port* _other
        )
{
    m_other = _other;
}

void Port::hasFileName(
        bool _bool,
        bool _cascade
        )
{
    m_hasFileName = _bool;
    update();


//    if(PortType::INPUT == getPortType())
//    {
//        foreach (Link* link, getConnections())
//        {
//            link->getPortFrom()->hasFileName(_bool, false);
//        }
//    }
//    else
//    {

//    }

}

Port::~Port(
        )
{
    foreach(Link* link, m_connections)
    {
        delete link;
    }
}
