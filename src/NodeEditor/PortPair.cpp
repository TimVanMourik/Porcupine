#include <QDomDocument>

#include "Argument.hpp"
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
        const Argument& _argument
        )
{
    m_name = _argument.getName();
//    m_dataType = _argument.getType();
    setPlainText(m_name);
}

const QString& PortPair::getName(
        ) const
{
    return m_name;
}

//const QVector<const DataType*>& PortPair::getType(
//        ) const
//{
//    return m_dataType;
//}

bool PortPair::hasAncestorPorts(
        )
{
    if(!m_input)
    {
        return false;
    }
    if(m_input->getConnectedPorts().length() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool PortPair::hasDescendantPorts(
        )
{
    if(!m_output)
    {
        return false;
    }
    if(m_output->getConnectedPorts().length() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QVector<PortPair*> PortPair::getAncestorPorts(
        )
{
    QVector<PortPair*> ports;
    if(!m_input)
    {
        return ports;
    }
    foreach(Port* port, m_input->getConnectedPorts())
    {
        PortPair* previous = port->getPortPair();
        ports.append(previous);
        foreach(PortPair* pair, previous->getAncestorPorts())
        {
            ports.append(pair);
        }
    }
    return ports;
}

QVector<PortPair*> PortPair::getDescendantPorts(
        )
{
    QVector<PortPair*> ports;
    if(!m_output)
    {
        return ports;
    }
    foreach(Port* port, m_output->getConnectedPorts())
    {
        PortPair* previous = port->getPortPair();
        ports.append(previous);
        foreach(PortPair* pair, previous->getDescendantPorts())
        {
            ports.append(pair);
        }
    }
    return ports;
}

QVector<const Node*> PortPair::getDescendantNodes(
        ) const
{
    QVector<const Node*> descendants;
    if(!m_output)
    {
        return descendants;
    }
    //Add children
    foreach(Port* port, m_output->getConnectedPorts())
    {
        const Node* child = port->getNode();
        if(!descendants.contains(child))
        {
            descendants.append(child);
        }
    }
    //And all descendants of children
    foreach (const Node* child, descendants)
    {
        QVector<const Node*> grandChildren = child->getDescendants();
        foreach (const Node* grandChild, grandChildren)
        {
            if(!descendants.contains(grandChild))
            {
                descendants.append(grandChild);
            }
        }
    }
    return descendants;
}

void PortPair::repositionPorts(
        qreal _width,
        qreal _height
        )
{
    if(m_input)
    {
        m_input->setPos(-_width / 2 - Port::getRadius(), _height);
    }
    if(m_output)
    {
        m_output->setPos(_width / 2 + Port::getRadius(), _height);
    }
}

bool PortPair::hasNodeAncestor(
        const Node* _node
        ) const
{
    if(m_node == _node)
    {
        return true;
    }
    if(m_input)
    {
        foreach(const Port* port, m_input->getConnectedPorts())
        {
            if(port)
            {
                if(port->getNode()->hasAncestor(_node))
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
        ) const
{
    QDomDocument xml;
    QDomElement newPortPair = xml.createElement("pair");
    newPortPair.setAttribute("name", getName());
    newPortPair.setAttribute("filename", getFileName());

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

void PortPair::fileNameChanged(
        const QString& _fileName,
        bool _cascadeUp
        )
{
    bool fileValid = !_fileName.isEmpty();
    //send file name up the tree
    if(_cascadeUp && hasAncestorPorts())
    {
        foreach (PortPair* port, getAncestorPorts())
        {
            port->fileNameChanged(_fileName, true);
        }
    }
    else
    //then send it down again (such that all branches are reached)
    {
        m_fileName = _fileName;
        foreach (PortPair* port, getDescendantPorts())
        {
            port->fileNameChanged(_fileName, false);
        }
    }
    if(m_input)
    {
        m_input->setHasFileName(fileValid);
    }
    if(m_output)
    {
        m_output->setHasFileName(fileValid);
    }
    emit changeFileName(_fileName);
}

const QString& PortPair::getFileName(
            ) const
{
    return m_fileName;
}

PortPair::~PortPair()
{
    delete m_input;
    delete m_output;
}

