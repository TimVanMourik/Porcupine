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

class QDomElement;

class Argument;
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
            NodeSetting* _setting = 0
            );
    //
    void loadFromNodeSetting(
            NodeSetting* _setting
            );
    ///@brief Returns a pointer to the new Port in case you need it (for example in loading a file)
//    Port* addPort(
//            const Argument* _name,
//            Port::PortType _isInput
//            );
    //
    void addPortPair(
            const Argument* _name,
            bool _isInput
            );
    //
    void connectPortsToPair(
            const Port* _input,
            const Port* _output
            );
    //
    void setName(
            const Argument* _argument
            );
    //
    void addInputPort(
            const Argument* _argument
            );
    //
    void addOutputPort(
            const Argument* _argument
            );
    //
    void addInputPorts(
            const QVector<Argument*>& _arguments
            );
    //
    void addOutputPorts(
            const QVector<Argument*>& _arguments
            );
    //
    void paint(
            QPainter* _painter,
            const QStyleOptionGraphicsItem* _option,
            QWidget* _widget
            );
    //
    void repositionPorts(
            qreal _width,
            qreal _height
            );
    //
    const QVector<PortPair*>& getPorts(
            ) const;
    //
    const QString& getName(
            ) const;
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
    bool isOffspringOf(
            const Node*
            ) const;
    //
    ~Node(
            );

private:
    //
    const NodeSetting* m_setting;
    //
    QGraphicsTextItem* m_nameLabel;
    //
    QVector<PortPair*> m_ports;
    //
    static qreal s_horizontalMargin;
    //
    static qreal s_verticalMargin;
    //
    static qreal s_textSpacing;
    //
    qreal m_width;
    //
    qreal m_height;
};

#endif // NODE_HPP
