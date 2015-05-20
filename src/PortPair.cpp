#include <QDomDocument>


#include "Argument.hpp"
//#include "DataType.hpp"
#include "Link.hpp"
#include "Node.hpp"
#include "Port.hpp"
#include "PortPair.hpp"

PortPair::PortPair(
        QGraphicsItem* _parent
        ) :
    QGraphicsTextItem(_parent),
    m_node((Node*)_parent),
    m_input(0),
    m_output(0),
    m_hasFileName(false)
{
}

void PortPair::createInputPort(
        )
{
    m_input = new Port((QGraphicsItem*) m_node);
    m_input->setPortType(Port::PortType::INPUT);
    m_input->setOther(m_output);
    m_input->setPortPair(this);
    if(m_output) m_output->setOther(m_input);
}

void PortPair::createOutputPort(
        )
{
    m_output = new Port((QGraphicsItem*) m_node);
    m_output->setPortType(Port::PortType::OUTPUT);
    m_output->setOther(m_input);
    m_output->setPortPair(this);
    if(m_input) m_input->setOther(m_output);
}

Port* PortPair::getInputPort(
        ) const
{
    return m_input;
}

Port* PortPair::getOutputPort(
        ) const
{
    return m_output;
}

void PortPair::setArgument(
        const Argument* _argument
        )
{
    m_name = _argument->getName();
    m_dataType = _argument->getType();
    setPlainText(m_name);
}

const QString& PortPair::getName(
        ) const
{
    return m_name;
}

const QVector<const DataType*>& PortPair::getType(
        ) const
{
    return m_dataType;
}

QVector<PortPair*> PortPair::getAncestors(
        )
{
    QVector<PortPair*> ports;
    foreach(Link* link, m_input->getConnections())
    {
        PortPair* previous = link->getPortFrom()->getPortPair();
        ports.append(previous);
        foreach(PortPair* pair, previous->getAncestors())
        {
            ports.append(pair);
        }
    }
    return ports;
}

QVector<PortPair*> PortPair::getDescendants(
        )
{
    QVector<PortPair*> ports;
    foreach(Link* link, m_output->getConnections())
    {
        PortPair* previous = link->getPortTo()->getPortPair();
        ports.append(previous);
        foreach(PortPair* pair, previous->getDescendants())
        {
            ports.append(pair);
        }
    }
    return ports;
}

bool PortPair::hasAncestor(
        const Node* _node
        ) const
{
    if(m_node == _node)
    {
        return true;
    }
    if(m_input)
    {
        foreach(const Link* link, m_input->getConnections())
        {
            Port* p = link->getPortFrom();
            if(p)
            {
                if(p->getNode()->hasAncestor(_node))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void PortPair::saveToXml(
        QDomElement& _xmlElement
        )
{
    QDomDocument xml;
    QDomElement newPortPair = xml.createElement("pair");
    newPortPair.setAttribute("name", getName());

    if(m_input)
    {
        m_input->saveToXml(newPortPair);
    }
    if(m_output)
    {
        m_output->saveToXml(newPortPair);
    }
    _xmlElement.appendChild(newPortPair);
}

void PortPair::loadFromXml(
        QDomElement& _xmlNode,
        QMap<quint64, Port*>& o_portMap
        )
{
    QDomNode portNode = _xmlNode.firstChild();
    while(!portNode.isNull())
    {
        QDomElement portElement = portNode.toElement();
        if(portElement.attribute("type").compare("input") == 0)
        {
            o_portMap[(quint64) portElement.attribute("identifier").toULongLong(0, 16)] = m_input;
        }
        else if(portElement.attribute("type").compare("output") == 0)
        {
            o_portMap[(quint64) portElement.attribute("identifier").toULongLong(0, 16)] = m_output;
        }
//        DataType* d = new DataType("");
//        Argument* argument = new Argument(portElement.attribute("name"), d);
        portNode = portNode.nextSibling();
    }
}

void PortPair::setFileName(
        bool _bool,
        const QString& _fileName,
        bool _cascade
        )
{
    m_hasFileName = _bool;
    m_fileName = _fileName;
    if(m_input)
    {
        m_input->setHasFileName(_bool);

    }
    if(m_output)
    {
        m_output->setHasFileName(_bool);
    }
    if(_cascade)
    {
        foreach (PortPair* port, getAncestors())
        {
            port->setFileName(_bool, _fileName, false);
        }
        foreach (PortPair* port, getDescendants())
        {
            port->setFileName(_bool, _fileName, false);
        }
    }
}


PortPair::~PortPair()
{
    delete m_input;
    delete m_output;
}

