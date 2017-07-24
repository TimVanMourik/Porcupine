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

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "Argument.hpp"
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

        Argument title(nodeJson["title"].toObject());
        QVector<Argument> ports;
        foreach (QJsonValue portObject, nodeJson["ports"].toArray())
        {
            ports << Argument(portObject.toObject());
        }

        NodeSetting* newNode = new NodeSetting(title, ports, nodeJson);
        newNode->setCategory(categories);
        m_nodeSettings[title.m_argumentName] = newNode;
        m_nodeNames << title.m_argumentName;
        newNodes << title.m_argumentName;
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




