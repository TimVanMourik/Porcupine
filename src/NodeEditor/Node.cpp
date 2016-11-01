/*
 * Copyright (C) 2014 Tim van Mourik
*/

#include <assert.h>

#include <QDomDocument>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
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
    m_setting(_setting),
    m_name(QString()),
    m_nameLabel(new QLineEdit()),
    m_ports(QVector<PortPair*>(0))
{
    m_antenna.setNode(this);
//    Preferences& preferences = Preferences::getInstance();
    _editor->scene()->addItem(this);
    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(m_nameLabel);

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::white);
    m_nameLabel->setPalette(palette);
    m_nameLabel->setStyleSheet("* {background-color: rgba(0, 0, 0, 0);}");
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

    if(m_setting) //false when loaded from file
    {
        m_name = _setting->getName();
        loadFromNodeSetting(_setting);
    }
    m_nameLabel->connect((QObject*) m_nameLabel, SIGNAL(textChanged(QString)), (QObject*) &m_antenna, SLOT(catchLabelChanged(QString)));
//    connect(m_nameLabel, SIGNAL(textChanged(QString)), this, SLOT(labelNameChanged(QString)));
}

void Node::loadFromNodeSetting(
        const NodeSetting* _setting
        )
{
    assert(_setting != 0);
    m_setting = _setting;
    m_name = m_setting->getName();
    m_nameLabel->setText(m_name);

    addPorts(_setting->getPorts(), true);
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

void Node::addPortPair(
        const Argument& _argument,
        bool _initialiseWithDefault
        )
{
    Preferences& preferences = Preferences::getInstance();
    PortPair* pair = new PortPair(this);
    pair->setArgument(_argument);
    pair->setDefaultTextColor(preferences.m_portTextColor);
    switch(_argument.getType())
    {
        case Argument::FieldType::INPUT :
            pair->createInputPort();
            break;
        case Argument::FieldType::INOUT :
            pair->createInputPort();
            pair->createOutputPort();
            break;
        case Argument::FieldType::OUTPUT :
            pair->createOutputPort();
            break;
        case Argument::FieldType::HIDDEN :
            pair->setVisible(false);
            break;
        case Argument::FieldType::NONE :
            pair->setVisible(false);
            break;
    }
    if(_initialiseWithDefault)
    {
        pair->fileNameChanged(_argument.getDefault(), false);
    }
    m_ports.append(pair);
}

void Node::repositionPorts(
        )
{
    //Expand the Node when the text is too large
    qreal width = s_horizontalMargin * 2;
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

const QString& Node::getType(
        ) const
{
    return m_setting->getName();
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

const NodeSetting* Node::getSetting(
        ) const
{
    return m_setting;
}

void Node::loadFromXml(
        QDomElement& _xmlNode,
        QMap<quint64, Port*>& o_portMap
        )
{
    Preferences& preferences = Preferences::getInstance();
    NodeLibrary& nodeLibrary = NodeLibrary::getInstance();

    QString nodeType = _xmlNode.attribute("type");
    const NodeSetting* setting = nodeLibrary.getNodeSetting(nodeType);
    assert(setting != 0);
    loadFromNodeSetting(setting);

    QString nodeName = _xmlNode.attribute("name");
    if(!nodeName.isEmpty())
    {
        m_nameLabel->setText(nodeName);
        labelNameChanged(nodeName);
    }

    QDomNode n = _xmlNode.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(e.tagName().compare("position") == 0)
        {
            setPos(e.attribute("x").toInt(), e.attribute("y").toInt());
        }
        else if(e.tagName().compare("pairs") == 0)
        {
            QDomNode portNode = e.firstChild();
            while(!portNode.isNull())
            {
                QDomElement portElement = portNode.toElement();
                PortPair* pair = 0;
                foreach(PortPair* port, m_ports)
                {
                    assert(port != 0);
                    if(port->getName().compare(portElement.attribute("name")) == 0)
                    {
                        pair = port;
                        QString name = portElement.attribute("filename");
                        if(!name.isEmpty())
                        {
                            pair->fileNameChanged(name, false);
                        }
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if(pair)
                {
                    pair->setDefaultTextColor(preferences.m_portTextColor);
                    pair->loadFromXml(portElement, o_portMap);
                }
                portNode = portNode.nextSibling();
            }
        }
        n = n.nextSibling();
    }
    repositionPorts();
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
