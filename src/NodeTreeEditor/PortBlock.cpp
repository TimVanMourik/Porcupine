/*  Copyright (C) Tim van Mourik, 2017, DCCN
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

#include <QCheckBox>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QLineEdit>

#include "PortBlock.hpp"
#include "PortPair.hpp"
#include "PortRow.hpp"

PortBlock::PortBlock(
        QWidget* _parent
        ) :
    QFormLayout(_parent)
{
    setRowWrapPolicy(QFormLayout::DontWrapRows);
    setVerticalSpacing(3);
    setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    setLabelAlignment(Qt::AlignBottom);
}

void PortBlock::addPortBlock(
        const QVector<PortPair*>& _ports
        )
{
    m_ports = _ports;
    foreach(PortPair* port, _ports)
    {
        addPortRow(port);
    }
}

void PortBlock::addPortRow(
        PortPair* port
        )
{
    PortRow* row = new PortRow(port, this);
    m_parameterNames[port->getName()] = row;
    addRow(port->getName(), row);
}

void PortBlock::removePortRow(
        PortRow* _row
        )
{
    m_parameterNames.remove(m_parameterNames.key(_row));
    removeRow(_row);
}

void PortBlock::saveToJson(
        QJsonObject& o_json
        )
{
    QJsonArray ports;
    foreach (PortRow* portRow, m_parameterNames.values())
    {
        QJsonObject portJson;
        portRow->saveToJson(portJson);
        ports << portJson;
    }
    o_json["ports"] = ports;
}

QString PortBlock::getParameterName(
        const QString& _portName
        ) const
{
    if(m_parameterNames[_portName])
    {
        return m_parameterNames[_portName]->getParameterName();
    }
    else
    {
        return QString("");
    }
}
