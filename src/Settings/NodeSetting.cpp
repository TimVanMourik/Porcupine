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

#include "QXmlSchema"
#include "QXmlSchemaValidator"

#include "NodeSetting.hpp"

NodeSetting::NodeSetting(
        const Argument& _name,
        const QVector<Argument>& _ports
        ) :
    m_name(_name),
    m_ports(_ports)
{
}

void NodeSetting::setColour(
        const QColor& _colour
        )
{
    m_nodeColour = _colour;
}

const QString& NodeSetting::getName(
        ) const
{
    return m_name.getName();
}

const Argument& NodeSetting::getTitle(
        ) const
{
    return m_name;
}

const QVector<Argument>& NodeSetting::getPorts(
        ) const
{
    return m_ports;
}

void NodeSetting::setCategory(
        const QStringList& _category
        )
{
    m_category = _category;
}

const QStringList& NodeSetting::getCategory(
        ) const
{
    return m_category;
}

NodeSetting::~NodeSetting(
        )
{
}
