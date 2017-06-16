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

#ifndef NODELIBRARY_HPP
#define NODELIBRARY_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file NodeLibrary.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <map>

#include <QDomDocument>
#include <QString>
#include <QtXmlPatterns>

#include "Singleton.hpp"

class DataType;
class NodeSetting;

class NodeLibrary : public Singleton<NodeLibrary>
{
    friend class Singleton<NodeLibrary>;
public:
    /// @brief The scema is an .xsd file in which the schema for a node xml-file is explained
    /// @param _schema is not const because .open() is not a const function (even in read-only mode)
    void setNodeSchema(
            QFile& _schema
            );
    /// @brief
    /// @param _schema is not const because .open() is not a const function (even in read-only mode)
    QStringList addNodeSetting(
            QFile& _node
            );
    /// @brief
    const NodeSetting* getNodeSetting(
            const QString& _nodeName
            );
    /// @brief
    const QStringList& getNodeNames(
        ) const ;
    /// @brief
    const QStringList getCategory(
            const QString& _setting
            ) const;
    /// @brief
    void save(
            QDataStream&
            );

private:
    /// @brief
    QMap<QString, NodeSetting*> m_nodeSettings;
    /// @brief
    QStringList m_nodeNames;
    /// @brief
    NodeLibrary(
            );
    /// @brief
    NodeLibrary(
            NodeLibrary const& _copy
            ); //Not implemented
    /// @brief
    NodeLibrary& operator=(
            NodeLibrary const& _copy
            ); //Not implemented
    /// @brief
    ~NodeLibrary(
            );
};

#endif // NODELIBRARY_HPP
