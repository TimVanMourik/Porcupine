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
    Singleton()
{
}

QStringList NodeLibrary::addNodeSetting(
        QFile& _schema
        )
{
    _schema.open(QIODevice::ReadOnly);
    QByteArray instanceText = _schema.readAll();
    QJsonObject json = QJsonDocument::fromJson(instanceText).object();
    if(json["nodes"].isNull())
    {
        std::cerr << "This node is invalid. It has an invalid structure.\n";
        return QStringList();
    }

    QStringList newNodes;
    foreach (QJsonValue node, json["nodes"].toArray())
    {
        QStringList categories;
        QJsonObject nodeJson = node.toObject();
        foreach (QJsonValue category, nodeJson["category"].toArray())
        {
            categories << category.toString();
        }

        Argument title;
        QJsonObject titleJson = nodeJson["title"].toObject();
        title.setName(titleJson["name"].toString());
        foreach (QJsonValue code, titleJson["code"].toArray())
        {
            QJsonObject codeJson = code.toObject();
            title.addCode(codeJson["language"].toString(),
                          codeJson["argument"].toString(),
                          codeJson["comment" ].toString());
        }
        QVector<Argument> nodes;
        foreach (QJsonValue portObject, nodeJson["ports"].toArray()) {
            QJsonObject portJson = portObject.toObject();
            bool input  = portJson["input"].toBool();
            bool output = portJson["output"].toBool();
            Argument port(portJson["name"].toString());
            if(input && output) {port.setType(Argument::FieldType::INOUT);}
            else if(input)      {port.setType(Argument::FieldType::INPUT);}
            else if(output)     {port.setType(Argument::FieldType::OUTPUT);}
            port.setDefault(portJson["value"].toString());
            port.setVisible(portJson["visible"].toBool());

            foreach (QJsonValue code, portJson["code"].toArray())
            {
                QJsonObject codeJson = code.toObject();
                port.addCode(codeJson["language"].toString(),
                             codeJson["argument"].toString(),
                             codeJson["comment" ].toString());
            }
            nodes << port;
        }

        NodeSetting* newNode = new NodeSetting(title, nodes);
        newNode->setCategory(categories);
        m_nodeSettings[title.getName()] = newNode;
        m_nodeNames << title.getName();
        newNodes << title.getName();
    }
    return newNodes;
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
    while(nodeIterator != m_nodeSettings.end())
    {
        delete nodeIterator.value();
        ++nodeIterator;
    }
}




