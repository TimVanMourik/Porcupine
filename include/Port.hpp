/*
 * Copyright (C) 2014 Tim van Mourik
*/

#ifndef PORT_HPP
#define PORT_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Port.h
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
    //
    Port(
            QGraphicsItem* _parent = 0
            );
    //
    void setNode(
            Node*
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
    bool removeLink(
            Link* _link
            );
    //
    PortType getPortType(
            ) const;
    //
    static qreal getRadius(
            );
    //
    void saveToXml(
            QDomElement& _xmlElement
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
    Node* m_node;
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
