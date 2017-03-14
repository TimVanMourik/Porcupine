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
        std::cerr << "Error: Nodes could not be loaded.\n";
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

QString NodeLibrary::addNodeSetting(
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
            Argument title;
            QVector<Argument> nodes;
            QDomNode node = docElem.firstChild();
            QStringList category;
            while(!node.isNull())
            {
                if(node.isElement())
                {
                    if(node.nodeName().compare("category") == 0)
                    {
                        category << node.attributes().namedItem("name").nodeValue();
                        QDomNode subCategory = node.firstChild();
                        while(!subCategory.isNull())
                        {
                            category << subCategory.attributes().namedItem("name").nodeValue();
                            subCategory = subCategory.firstChild();
                        }
                    }
                    else if(node.nodeName().compare("title") == 0)
                    {
                        title.setName(node.attributes().namedItem("name").nodeValue());
                        // if there is a code block
                        QDomNode code = node.firstChild();
                        if(!code.isNull() && code.nodeName().compare("code") == 0)
                        {
                            QDomNode codeBlock = code.firstChild();
                            while(!codeBlock.isNull())
                            {
                                if(codeBlock.nodeName().compare("language") == 0)
                                {
                                    QString language, argument, comment;
                                    parseCodeBlock(codeBlock, language, argument, comment);
                                    title.addCode(language, argument, comment);
                                }
                                codeBlock = codeBlock.nextSibling();
                            }
                        }
                    }
                    else
                    {
                        Argument codeArgument(node.attributes().namedItem("name").nodeValue());
                        codeArgument.setDefault(node.attributes().namedItem("default").nodeValue());
                        QString editable = node.attributes().namedItem("editable").nodeValue();
                        if(editable.compare("true", Qt::CaseInsensitive) == 0)
                        {
                            codeArgument.setEditable(true);
                        }
                        else if(editable.compare("false", Qt::CaseInsensitive) == 0)
                        {
                            codeArgument.setEditable(false);
                        }
                        if(node.nodeName().compare("title") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::NONE);
                        }
                        else if(node.nodeName().compare("input") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::INPUT);
                        }
                        else if(node.nodeName().compare("input-output") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::INOUT);
                        }
                        else if(node.nodeName().compare("output") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::OUTPUT);
                        }
                        else if(node.nodeName().compare("hidden") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::HIDDEN);
                        }
                        else if(node.nodeName().compare("none") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::NONE);
                        }
                        else if(node.nodeName().compare("secret") == 0)
                        {
                            codeArgument.setType(Argument::FieldType::SECRET);
                        }
                        else ///@todo think of how to handle a block with a different name
                        {
                            codeArgument.setType(Argument::FieldType::NONE);
                        }
                        // if there is a code block
                        QDomNode code = node.firstChild();
                        if(!code.isNull() && code.nodeName().compare("code") == 0)
                        {
                            QDomNode codeBlock = code.firstChild();
                            while(!codeBlock.isNull())
                            {
                                if(codeBlock.nodeName().compare("language") == 0)
                                {
                                    QString language, argument, comment;
                                    parseCodeBlock(codeBlock, language, argument, comment);
                                    codeArgument.addCode(language, argument, comment);
                                }
                                codeBlock = codeBlock.nextSibling();
                            }
                        }
                        nodes.append(codeArgument);
                    }
                    node = node.nextSibling();
                }
            }
//            std::cout << title.toStdString() << std::endl;
            NodeSetting* newNode = new NodeSetting(title, nodes);
            newNode->setCategory(category);
            m_nodeSettings[title.getName()] = newNode;
            m_nodeNames << title.getName();
            return title.getName();
        }
        else
        {
            std::cerr << "This node is invalid. The root is not a node.\n";
            return QString("");
        }
    }
    else
    {
        std::cerr << "This node is invalid. It has an invalid structure.\n";
        return QString("");
    }
}

void NodeLibrary::parseCodeBlock(
        const QDomNode& _codeBlock,
        QString& o_language,
        QString& o_argument,
        QString& o_comment
        )
{
    o_language = _codeBlock.attributes().namedItem("name").nodeValue();
    QDomNode argumentBlock = _codeBlock.firstChild();
    while(!argumentBlock.isNull())
    {
        if(argumentBlock.nodeName().compare("argument") == 0)
        {
            o_argument = argumentBlock.attributes().namedItem("name").nodeValue();
        }
        else if(argumentBlock.nodeName().compare("comment") == 0)
        {
            o_comment = argumentBlock.attributes().namedItem("text").nodeValue();
        }
        argumentBlock = argumentBlock.nextSibling();
    }
}

const QStringList NodeLibrary::getCategory(
        const QString& _setting
        ) const
{
    return m_nodeSettings[_setting]->getCategory();
}

const NodeSetting* NodeLibrary::getNodeSetting(
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
    QMap<QString, NodeSetting*>::iterator nodeIterator = m_nodeSettings.begin();
//    std::cerr << "NodeLibrary Destructed\n";
//    std::cout << m_nodeSettings.size() << std::endl;
    while(nodeIterator != m_nodeSettings.end())
    {
//        std::cerr << "Deleting NodeSetting...\n";
        delete nodeIterator.value();
        ++nodeIterator;
    }

    QMap<QString, DataType*>::iterator dataIterator = m_dataTypes.begin();
    while(dataIterator != m_dataTypes.end())
    {
        delete dataIterator.value();
        ++dataIterator;
    }

    delete m_nodeValidator;
}












