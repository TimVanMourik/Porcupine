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

#ifndef NODE_HPP
#define NODE_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Node.hpp
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QGraphicsPathItem>
#include <QJsonObject>

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
    Node(
            NodeEditor* _editor,
            const QJsonObject& _object
            );
    //
    PortPair* addPortPair(
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
    void removePort(
            PortPair* _port
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
    const QJsonObject& toJson(
            ) const;
    //
    void updateJson(
            );
    //
    const QVector<PortPair*>& getPorts(
            ) const;
    //
    const QString& getType(
            ) const;
    //
    const QString& getBaseName(
            ) const;
    //
    const QString& getName(
            ) const;
    //
    const NodeAntenna& getAntenna(
            ) const;
    //
    const QJsonObject& getJson(
            ) const;
    //
    int type(
            ) const;
    //
    void loadFromJson(
            const QJsonObject& _json,
            QMap<quint64, Port*>& o_portMap
            );
    //
    void loadPortsFromJson(
            const QJsonArray& _json,
            QMap<quint64, Port*>& o_portMap
            );
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
    unsigned int generateId(
            );
    //
    void initialize(
            );
    //
    ~Node(
            );
private:
    //
    void loadFromNodeSetting(
            const NodeSetting* _setting
            );
    //
    QJsonObject m_json;
    //
    QString m_name;
    //
    QString m_baseName;
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
