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

#ifndef PORT_HPP
#define PORT_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Port.hpp
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QGraphicsPathItem>

class Link;
class Node;
class PortPair;
class QDomElement;

class Port : public QGraphicsPathItem
{
public:
    //
    enum {
        Type = QGraphicsItem::UserType + 3
    };
    //
    enum PortType
    {
        NONE = 0,
        INPUT = 1,
        OUTPUT = 2
    };
    //Node as parent, because positions are relative to node location
    Port(
            const Node* _node = 0
            );
    //
    void setPortPair(
            PortPair* _pair
            );
    //
    void setPortType(
            PortType _type
            );
    //
    void addConnection(
            Link* _newLink
                       );
    //
    bool isConnectedTo(
            Port*
            );
    //
    Port* other(
            ) const;
    //
    const QString& getName(
            ) const;
    //
    const Node* getNode(
            ) const;
    //
    PortPair* getPortPair(
            ) const;
    //
    const QVector<Link*>& getConnections(
            ) const;
    //
    QVector<Port*> getConnectedPorts(
            ) const;
    //
    bool hasFileName(
            ) const;
    //
    void removeLink(
            Link* _link
            );
    //
    PortType getPortType(
            ) const;
    //
    static qreal getRadius(
            );
    //
    void paint(
            QPainter* _painter,
            const QStyleOptionGraphicsItem* _option,
            QWidget* _widget
            );
    // For when the port is clicked
    int type(
            ) const;
    //
    void setHasFileName(
            bool _bool
            );
    //
    void fileNameChanged(
            const QString& _fileName = "",
            bool _cascadeUp = true
            );
    //
    const QString& getFileName(
            ) const;
    //
    void setOther(
            Port* _other
            );
    //
    ~Port(
            );
private:
    //
    QVariant itemChange(
            GraphicsItemChange change,
            const QVariant &value
            );

    // A pointer to the Node to which the Port belongs
    const Node* m_node;
    // If this is an input port, m_other point to the output and vice versa.
    // m_other = 0 when the output does not have an input.
    Port* m_other;
    //
    PortPair* m_pair;
    // The list of Links that end or start at this Port
    QVector<Link*> m_connections;
    // A boolean value that states if the Port is input or output
    PortType m_type;
    // The margin away from the port that is kept empty
    static qreal s_margin;
    // The size of the Port being displayed
    static qreal s_radius;
    //
    bool m_hasFileName;
};

#endif // PORT_HPP
