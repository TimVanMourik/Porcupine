/*
 * Copyright (C) 2014 Tim van Mourik
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
