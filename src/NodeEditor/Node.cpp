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

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLineEdit>
#include <QLinearGradient>

#include "Argument.hpp"
#include "Node.hpp"
#include "NodeEditor.hpp"
#include "NodeLibrary.hpp"
#include "NodeSetting.hpp"
#include "Preferences.hpp"
#include "PortPair.hpp"

qreal Node::s_horizontalMargin  = 5;
qreal Node::s_verticalMargin    = 3;
qreal Node::s_textSpacing       = 1;

Node::Node(
        NodeEditor* _editor,
        const NodeSetting* _setting
        ) :
    QGraphicsPathItem(0),
    m_json(QJsonObject()),
    m_name(QString()),
    m_nameLabel(new QLineEdit()),
    m_ports(QVector<PortPair*>(0))
{
    _editor->scene()->addItem(this);
    initialize();
    if(_setting) loadFromNodeSetting(_setting);
    m_nameLabel->connect((QObject*) m_nameLabel, SIGNAL(textChanged(QString)), (QObject*) &m_antenna, SLOT(catchLabelChanged(QString)));
}

Node::Node(
        NodeEditor* _editor,
        const QJsonObject& _object
        ) :
    QGraphicsPathItem(0),
    m_json(QJsonObject()),
    m_name(QString()),
    m_nameLabel(new QLineEdit()),
    m_ports(QVector<PortPair*>(0))
{
    _editor->scene()->addItem(this);
    initialize();
    QMap<quint64, Port*> portMap;
    loadFromJson(_object, portMap);
    m_nameLabel->connect((QObject*) m_nameLabel, SIGNAL(textChanged(QString)), (QObject*) &m_antenna, SLOT(catchLabelChanged(QString)));
}

void Node::initialize(
        )
{
    m_antenna.setNode(this);
//    Preferences& preferences = Preferences::getInstance();
    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(m_nameLabel);

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::white);
    m_nameLabel->setPalette(palette);

    QFile styleFile(":/qss/translucentLabel.qss");
    styleFile.open(QFile::ReadOnly);
    QString translucentLabel = QString::fromLatin1(styleFile.readAll());
    m_nameLabel->setStyleSheet(translucentLabel);

    QFont font(scene()->font());
    font.setBold(true);
    m_nameLabel->setFont(font);
    m_nameLabel->setText(m_name);
    m_nameLabel->setFrame(false);
    m_nameLabel->setAttribute(Qt::WA_TranslucentBackground);
//    m_nameLabel->setDefaultTextColor(preferences.getPortTextColor());

    QPainterPath path;
    path.addRect(0, 0, 0, 0);
    setPath(path);
    setPen(QPen(Qt::darkRed));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void Node::loadFromNodeSetting(
        const NodeSetting* _setting
        )
{
    assert(_setting != 0);
    m_json = _setting->getJson();
    Argument title(m_json["title"].toObject());
    m_name = title.m_argumentName;
    m_nameLabel->setText(m_name);

    QVector<Argument> ports;
    foreach (QJsonValue portObject, m_json["ports"].toArray())
    {
        ports << Argument(portObject.toObject());
    }
    addPorts(ports, true);
    repositionPorts();
}

void Node::addPorts(
        const QVector<Argument>& ports,
        bool _initialiseWithDefault
        )
{
    foreach(const Argument& argument, ports)
    {
        addPortPair(argument, _initialiseWithDefault);
    }
}

void Node::addPort(
        const Argument& _argument,
        bool _initialiseWithDefault
        )
{
    addPortPair(_argument, _initialiseWithDefault);
}

PortPair* Node::addPortPair(
        const Argument& _argument,
        bool _initialiseWithDefault
        )
{
    Preferences& preferences = Preferences::getInstance();
    PortPair* pair = new PortPair(this);
    pair->setArgument(_argument);
    pair->setDefaultTextColor(preferences.m_portTextColor);
    if(_argument.m_isInput)   pair->createInputPort(_argument.m_isVisible);
    if(_argument.m_isOutput)  pair->createOutputPort(_argument.m_isVisible);
    _argument.m_isVisible ? pair->setVisible(true) : pair->setVisible(false);

    if(_initialiseWithDefault)
    {
        pair->fileNameChanged(_argument.m_defaultValue, false);
    }
    m_ports.append(pair);
    return pair;
}

void Node::removePort(
        PortPair* _port
        )
{
    m_ports.removeOne(_port);
    repositionPorts();
}

void Node::repositionPorts(
        )
{
    //Expand the Node when the text is too large
    qreal width  = s_horizontalMargin * 2;
    qreal height = s_verticalMargin;

    width  += m_nameLabel->fontMetrics().width(m_name);
    height += m_nameLabel->fontMetrics().height() + s_horizontalMargin;
    m_nameLabel->setMinimumWidth(width);
    m_nameLabel->setMaximumWidth(width);

    foreach (const PortPair* port, m_ports)
    {
        if(!port->isVisible())
        {
            continue;
        }
        qreal textWidth  = port->boundingRect().width();
        qreal textHeight = port->boundingRect().height();

        if(textWidth > width - s_horizontalMargin * 2)
        {
            width = textWidth + s_horizontalMargin * 2;
        }
        height += textHeight + s_textSpacing;
    }
    height += s_verticalMargin;

    QPainterPath path;
    path.addRect(-width / 2, -height / 2, width, height);
    setPath(path);
    int y = s_verticalMargin - height / 2;
    m_nameLabel->move(-m_nameLabel->fontMetrics().width(m_name) / 2, y);

    y += m_nameLabel->fontMetrics().height() * 2 + s_textSpacing * 4;

    foreach (PortPair* port, m_ports)
    {
        if(!port->isVisible())
        {
            continue;
        }
        qreal textHeight = port->boundingRect().height();
        port->setPos(-port->boundingRect().width() / 2, y - textHeight / 2);
        port->repositionPorts(width, y);
        y += textHeight + s_textSpacing;
    }
}

void Node::paint(
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
        _painter->setPen(preferences.m_nodePenSelected);
        _painter->setBrush(preferences.m_nodeBrushSelected);
    }
    else
    {
        _painter->setPen(preferences.m_nodePenUnselected);
        _painter->setBrush(preferences.m_nodeBrushUnselected);
    }
    _painter->drawPath(path());
}

int Node::type(
        ) const
{
    return Type;
}

const QString& Node::getName(
        ) const
{
    return m_name;
}

const NodeAntenna& Node::getAntenna(
        ) const
{
    return m_antenna;
}

const QJsonObject& Node::getJson(
        ) const
{
    return m_json;
}

void Node::loadFromJson(
        const QJsonObject& _json,
        QMap<quint64, Port*>& o_portMap
        )
{
    Argument title(_json["title"].toObject());
    m_json = _json;
    m_name = title.m_argumentName;
    m_nameLabel->setText(m_name);
    QJsonArray position = _json["position"].toArray();
    setPos(position.at(0).toDouble(0), position.at(1).toDouble(0));
    foreach (QJsonValue portValue, _json["ports"].toArray()) {
        QJsonObject portObject = portValue.toObject();
//        qDebug() << portObject;
        PortPair* p = addPortPair(Argument(portObject));
        if(!portObject["value"].isNull())
        {
            ///@todo check if this is right. If so, put comments.
            p->fileNameChanged(portObject["value"].toString(), false);
            QJsonValue inputPort  = portObject["inputPort"];
            QJsonValue outputPort = portObject["outputPort"];
//            qDebug() << p->getInputPort ();
//            qDebug() << p->getOutputPort();
            if(!inputPort.isNull())  o_portMap[(quint64)  inputPort.toString().toULongLong(0, 16)] = p->getInputPort();
            if(!outputPort.isNull()) o_portMap[(quint64) outputPort.toString().toULongLong(0, 16)] = p->getOutputPort();
        }
    }
    repositionPorts();
}

void Node::updateJson(
        )
{
    QJsonArray ports;
    foreach (PortPair* port, m_ports)
    {
        ports << port->toJson();
    }
    m_json["ports"] = ports;
}

const QJsonObject& Node::toJson(
        ) const
{
    return m_json;
}

bool Node::hasAncestor(
        const Node* _node
        ) const
{
    if(this == _node)
    {
        return true;
    }

    foreach(const PortPair* port, m_ports)
    {
        if(port->hasNodeAncestor(_node))
        {
            return true;
        }
    }
    return false;
}

QVector<const Node*> Node::getDescendants(
        ) const
{
    QVector<const Node*> descendants;
    //Add children
    foreach(const PortPair* port, m_ports)
    {
        QVector<const Node*> portDescendant = port->getDescendantNodes();
        foreach (const Node* descendant, portDescendant)
        {
            if(!descendants.contains(descendant))
            {
                descendants.append(descendant);
            }
        }
    }
    return descendants;
}

const QVector<PortPair*>& Node::getPorts(
        ) const
{
    return m_ports;
}

void Node::labelNameChanged(
        const QString& _name
        )
{
    m_name = _name;
    repositionPorts();
    m_antenna.sendLabelChanged(_name);
}

QVariant Node::itemChange(
        GraphicsItemChange _change,
        const QVariant& _value
        )
{
    if (_change == QGraphicsItem::ItemSelectedChange)
    {
        //explicitly equate it to true and false, because it's a QVariant
        if (_value == true)
        {
            m_antenna.sendNodeSelected(true);
        }
        else if (_value == false)
        {
            m_antenna.sendNodeSelected(false);
        }
    }
    return QGraphicsItem::itemChange(_change, _value);
}

Node::~Node()
{
    foreach(PortPair* port, m_ports)
    {
        delete port;
    }
}
