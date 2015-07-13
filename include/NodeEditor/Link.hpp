/*
 * Copyright (C) 2014 Tim van Mourik
*/

#ifndef LINK_HPP
#define LINK_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Link.h
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
    void saveToXml(
            QDomElement& _xmlElement
            );
    //
    void loadFromXml(
            QDomElement& _xmlNode,
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
