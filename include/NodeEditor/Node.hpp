/*
 * Copyright (C) 2014 Tim van Mourik
*/

#ifndef NODE_HPP
#define NODE_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Node.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QGraphicsPathItem>

#include "NodeAntenna.hpp"

class QDomElement;
class QLineEdit;
class QObject;

class Argument;
class DataType;
class NodeEditor;
class NodeSetting;
class Port;
class PortPair;

class Node : public QGraphicsPathItem
{
public:
    //
    enum
    {
        Type = QGraphicsItem::UserType + 2
    };

    //
    Node(
            NodeEditor* _editor,
            const NodeSetting* _setting = 0
            );
    //
    void addPortPair(
            const Argument& _name,
            bool _initialiseWithDefault = false
            );
    //
    void connectPortsToPair(
            const Port* _input,
            const Port* _output
            );
    //
    void addPort(
            const Argument& _argument,
            bool _initialiseWithDefault = false
            );
    //
    void addPorts(
            const QVector<Argument>& _arguments,
            bool _initialiseWithDefault = false
            );
    //
    void paint(
            QPainter* _painter,
            const QStyleOptionGraphicsItem* _option,
            QWidget* _widget
            );
    //
    void repositionPorts(
            );
    //
    const QVector<PortPair*>& getPorts(
            ) const;
    //
    const QString& getType(
            ) const;
    //
    const QString& getName(
            ) const;
    //
    const NodeAntenna& getAntenna(
            ) const;
    //
    const NodeSetting* getSetting(
            ) const;
    //
    int type(
            ) const;
    //
    void loadFromXml(
            QDomElement& _xmlNode,
            QMap<quint64, Port*>& o_portMap
            );
    //
//    QVector<const Node*> getAncestors(
//            ) const;
    /// @brief returns an in-order list of descendants that are input-output connected via Links.
    QVector<const Node*> getDescendants(
            ) const;
    //
    bool hasAncestor(
            const Node*
            ) const;
    //
    void labelNameChanged(
            const QString& _name
            );
    //
    QVariant itemChange(
            GraphicsItemChange _change,
            const QVariant& _value
            );
    //
    ~Node(
            );
//signals:
//    //
//    void nodeNameChanged(
//            const QString& _name
//            );
private:
    //
    void loadFromNodeSetting(
            const NodeSetting* _setting
            );
    //
    const NodeSetting* m_setting;
    //
    QString m_name;
    // As Node is not a QObject derivative, but we would still like to use signals and slots, transmissions go via an antenna
    // Another way to appraoch the problem is multiple inheritance.
    NodeAntenna m_antenna;
    //
    QLineEdit* m_nameLabel;
    //
    QVector<PortPair*> m_ports;
    //
    static qreal s_horizontalMargin;
    //
    static qreal s_verticalMargin;
    //
    static qreal s_textSpacing;
};

#endif // NODE_HPP
