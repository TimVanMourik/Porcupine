/*
 * Copyright (C) 2014 Tim van Mourik
*/

#include "QXmlSchema"
#include "QXmlSchemaValidator"

#include "NodeSetting.hpp"

NodeSetting::NodeSetting(
        const Argument& _name,
        const QVector<Argument>& _inputPortNames,
        const QVector<Argument>& _outputPortNames
        ) :
    m_name(_name),
    m_inputPortNames(_inputPortNames),
    m_outputPortNames(_outputPortNames)
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

const QVector<Argument>& NodeSetting::getInput(
        ) const
{
    return m_inputPortNames;
}

const QVector<Argument>& NodeSetting::getOutput(
        ) const
{
    return m_outputPortNames;
}

NodeSetting::~NodeSetting(
        )
{
}
