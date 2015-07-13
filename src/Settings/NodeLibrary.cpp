/*
 * Copyright (C) 2014 Tim van Mourik
*/

#include <iostream>
#include <cstring>
#include <QDomDocument>
#include <QXmlStreamReader>

#include "Argument.hpp"
#include "DataType.hpp"
#include "NodeLibrary.hpp"
#include "NodeSetting.hpp"

NodeLibrary::NodeLibrary() :
    Singleton(),
    m_nodeValidator(0)
{
}

void NodeLibrary::setDataTypeSchema(
        QFile& _typeSchema
        )
{
    _typeSchema.open(QIODevice::ReadOnly);
    QXmlSchema xmlSchema;
    xmlSchema.load(_typeSchema.readAll());
    if (!xmlSchema.isValid())
    {
        std::cerr << "Error: Nodes cold not be loaded.\n";
    }
    m_nodeValidator = new QXmlSchemaValidator(xmlSchema);
}

void NodeLibrary::setNodeSchema(
        QFile& _nodeSchema
        )
{
    _nodeSchema.open(QIODevice::ReadOnly);
    QXmlSchema xmlSchema;
    xmlSchema.load(_nodeSchema.readAll());
    if (!xmlSchema.isValid())
    {
        std::cerr << "Error: Nodes cold not be loaded.\n";
    }
    m_nodeValidator = new QXmlSchemaValidator(xmlSchema);
}

void NodeLibrary::addDataTypes(
        QFile& _schema
        )
{
    QDomDocument document;
    if(!_schema.open(QIODevice::ReadOnly))
    {
        std::cerr << "Error: cannot open file.\n";
        return;
    }

    if(!document.setContent(&_schema))
    {
        std::cerr << "Error: cannot read file.\n";
        _schema.close();
        return;
    }
    _schema.reset();
    QByteArray instanceText = _schema.readAll();
    if(!m_nodeValidator->validate(instanceText))
    {
        std::cerr << "Error: The data type file has an incorrect format.\n";
        _schema.close();
        return;
    }

    QDomElement docElement = document.documentElement();
    QDomNode n = docElement.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(e.tagName().compare("typename") == 0)
        {
            QString title;
            title = e.firstChild().nodeValue();
            m_dataTypes[title] = new DataType(title);
            m_typeNames << title;
        }
        n = n.nextSibling();
    }
}

void NodeLibrary::addNodeSetting(
        QFile& _schema
        )
{
    _schema.open(QIODevice::ReadOnly);
    QByteArray instanceText = _schema.readAll();
    if(m_nodeValidator->validate(instanceText))
    {
        _schema.reset();
        QDomDocument document;
        document.setContent(&_schema);
        _schema.close();

        QDomElement docElem = document.documentElement();
        QString rootTag = docElem.tagName();
        if(std::strcmp(rootTag.toStdString().c_str(), "node") == 0)
        {
//            std::cerr << rootTag.toStdString() << "\n"; //Should print 'node'
            QString title;
            QVector<Argument*> inputNodes;
            QVector<Argument*> outputNodes;
            QDomNode node = docElem.firstChild();
            while(!node.isNull())
            {
                if(node.isElement())
                {
//                    QDomElement nodeValue = node.toElement();
//                    std::cerr << node.toDocument().nodeName().toStdString() << "\n";
                    if(std::strcmp(node.nodeName().toStdString().c_str(), "title") == 0)
                    {
                        title = node.firstChild().nodeValue();
//                        std::cout << "title = " << node.firstChild().nodeValue().toStdString() << std::endl;
                    }
                    else if(std::strcmp(node.nodeName().toStdString().c_str(), "input") == 0)
                    {
                        QDomNamedNodeMap attributes = node.attributes();
                        QDomNode nodeName = attributes.namedItem("name");
                        QDomNode className = attributes.namedItem("class");
//                        std::cout << "nodeName = " << nodeName.nodeValue().toStdString() << std::endl;

                        if(nodeName.isNull() || className.isNull() || m_dataTypes[className.nodeValue()] == NULL)
                        {
//                            std::cerr << className.nodeValue().toStdString() << " " << m_dataTypes[className.nodeValue()] << "\n";
                            std::cerr << "This node is invalid: the input name is empty or the data type is invalid.\n";
                            return;
                        }
                        QString name = nodeName.nodeValue();
                        QVector<const DataType*> type;
                        type.append(m_dataTypes[className.nodeValue()]);
                        Argument* argument = new Argument(name, type);

                        inputNodes.append(argument);
                    }
                    else if(std::strcmp(node.nodeName().toStdString().c_str(), "output") == 0)
                    {
                        QDomNamedNodeMap attributes = node.attributes();
                        QDomNode nodeName = attributes.namedItem("name");
                        QDomNode className = attributes.namedItem("class");

                        if(nodeName.isNull() || className.isNull() || m_dataTypes[className.nodeValue()] == NULL)
                        {
                            std::cerr << "This node is invalid: the output name is empty or the data type is invalid.\n";
                            return;
                        }
                        QString name = nodeName.nodeValue();
                        QVector<const DataType*> type;
                        type.append(m_dataTypes[className.nodeValue()]);
                        Argument* argument = new Argument(name, type);

                        outputNodes.append(argument);
                    }
                    node = node.nextSibling();
                }
            }
//            std::cout << title.toStdString() << std::endl;
            m_nodeSettings[title] = new NodeSetting(title, inputNodes, outputNodes);
            m_nodeNames << title;
        }
        else
        {
            std::cerr << "This node is invalid. The root is not a node.\n";
            return;
        }
    }
    else
    {
        std::cerr << "This node is invalid. It has an invalid structure.\n";
        return;
    }
}

NodeSetting* NodeLibrary::getNodeSetting(
        const QString& _nodeName
        ) /*const*/
{
    return m_nodeSettings[_nodeName];
}

const QStringList& NodeLibrary::getNodeNames(
        ) const
{
    return m_nodeNames;
}

NodeLibrary::~NodeLibrary()
{
    std::map <QString, NodeSetting*>::iterator nodeIterator = m_nodeSettings.begin();
//    std::cerr << "NodeLibrary Destructed\n";
//    std::cout << m_nodeSettings.size() << std::endl;
    while(nodeIterator != m_nodeSettings.end())
    {
//        std::cerr << "Deleting NodeSetting...\n";
        delete (*nodeIterator).second;
        ++nodeIterator;
    }

    std::map <QString, DataType*>::iterator dataIterator = m_dataTypes.begin();
    while(dataIterator != m_dataTypes.end())
    {
        delete (*dataIterator).second;
        ++dataIterator;
    }

    delete m_nodeValidator;
}












