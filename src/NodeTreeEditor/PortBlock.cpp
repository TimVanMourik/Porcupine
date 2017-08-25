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
#include <QInputDialog>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QFormLayout>
#include <QPushButton>

#include "Node.hpp"
#include "PortBlock.hpp"
#include "PortPair.hpp"
#include "PortRow.hpp"

PortBlock::PortBlock(
        Node* _node,
        QWidget* _parent
        ) :
    QWidget(_parent),
    m_node(_node)
{
    new QVBoxLayout(this);
    QWidget* w = new QWidget(this);
    layout()->addWidget(w);
    m_layout = new QFormLayout(w);
    m_layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
    m_layout->setVerticalSpacing(3);
    m_layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    m_layout->setLabelAlignment(Qt::AlignBottom);

    addPortBlock(m_node->getPorts());
    QLabel* baseNameLabel = new QLabel(m_node->getBaseName());
    baseNameLabel->setStyleSheet("QLabel { color : rgb(0.7, 0.7, 0.7); }");
    QFont labelFont;
    labelFont.setItalic(true);
    labelFont.setPixelSize(10);

    baseNameLabel->setFont(labelFont);
    layout()->addWidget(baseNameLabel);
    layout()->setAlignment(baseNameLabel, Qt::AlignCenter);
    QPushButton* addPortButton = new QPushButton("Add port");
    layout()->addWidget(addPortButton);
    //This removes the ugly label background
//    setObjectName("myObject");
    setStyleSheet("QLabel {background-color: rgba(0, 0, 0, 0);}");

    connect(addPortButton, SIGNAL(clicked(bool)), this, SLOT(addPort()));
}

void PortBlock::addPort(
        )
{
    Argument portArgument;
    portArgument.m_isVisible = true;
    portArgument.m_isIterator = false;
    portArgument.m_isEditable = true;
    QString portTitle = QInputDialog::getText(this, "Port name", "Please enter the port name");
    if(portTitle.isEmpty())
    {
        return;
    }
    portArgument.m_argumentName = portTitle;

    QMessageBox ioBox;
    ioBox.setText(tr("Do you want an input or output port, or both?"));
    QAbstractButton* input  = ioBox.addButton(tr("Input"),  QMessageBox::YesRole);
    QAbstractButton* output = ioBox.addButton(tr("Output"), QMessageBox::YesRole);
    QAbstractButton* both   = ioBox.addButton(tr("Both"),   QMessageBox::YesRole);
    ioBox.exec();

    Argument title(m_node->getJson()["title"].toObject());
    if(ioBox.clickedButton() == input)
    {
        portArgument.m_isInput  = true;
        portArgument.m_isOutput = false;
        QList<QString> languages = title.getLanguages();
        foreach (QString language, languages)
        {
            QMap<QString, QString> argument;
            argument["name"] = portTitle;
            portArgument.addCode(language, argument);
        }
    }
    else if(ioBox.clickedButton() == output)
    {
        portArgument.m_isInput  = false;
        portArgument.m_isOutput = true;
        QList<QString> languages = title.getLanguages();
        foreach (QString language, languages)
        {
            QMap<QString, QString> argument;
            argument["name"] = portTitle;
            portArgument.addCode(language, argument);
        }
    }
    else if(ioBox.clickedButton() == both)
    {
        portArgument.m_isInput  = true;
        portArgument.m_isOutput = true;
        QList<QString> languages = title.getLanguages();
        foreach (QString language, languages)
        {
            QMap<QString, QString> argument;
            argument["name"] = portTitle;
            portArgument.addCode(language, argument);
        }
    }
    else
    {
        return;
    }

    portArgument.updateJson();
    PortPair* p = m_node->addPortPair(portArgument, false);
    m_node->repositionPorts();
    addPortRow(p);
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
    m_layout->addRow(port->getName(), row);
}

void PortBlock::removePortRow(
        PortRow* _row
        )
{
    m_parameterNames.remove(m_parameterNames.key(_row));
    // The lines below can be replaced by the remove row line once Qt 5.8.0 is default
    int i = m_layout->indexOf(_row);
    delete m_layout->takeAt(i)->widget();
    delete m_layout->takeAt(i - 1)->widget();
//    m_layout->removeRow(_row);
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
