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
    const QString& getName(
            ) const;
    //
    const Node* getNode(
            ) const;
    //
    const QVector<Link*>& getConnections(
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
    // For when the port is clicked
    int type(
            ) const;
//    void loadFromXml(
//            QDomElement& _xmlNode,
//            QMap<quint64, Port*>& o_portMap
//            );
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
    // The list of Links that end or start at this Port
    QVector<Link*> m_connections;
    // A boolean value that states if the Port is input or output
    PortType m_type;
    // The margin away from the port that is kept empty
    static qreal s_margin;
    // The size of the Port being displayed
    static qreal s_radius;
};

#endif // PORT_HPP
