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
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

#include "PortBlock.hpp"
#include "PortPair.hpp"
#include "PortRow.hpp"

PortRow::PortRow(
        PortPair* _port,
        PortBlock* _parent
        ) :
    QWidget(),
    m_parent(_parent),
    m_port(_port),
    m_parameterName(new QLineEdit()),
    m_showCheckbox(new QCheckBox()),
    m_iterateCheckbox(0),
    m_deleteButton(new QPushButton())
{
    m_parameterName->setPlaceholderText("<value>");
    QString name = _port->getFileName();
    if(!name.isEmpty()) m_parameterName->setText(name);
    QHBoxLayout* rowLayout = new QHBoxLayout(this);
    rowLayout->addWidget(m_parameterName);
    rowLayout->addWidget(m_showCheckbox);
    if(_port->getInputPort())
    {
        m_iterateCheckbox = new QCheckBox();
        m_iterateCheckbox->setChecked(_port->getArgument().isIterator());
        rowLayout->addWidget(m_iterateCheckbox);
        connect(m_iterateCheckbox, SIGNAL(toggled(bool)), this, SLOT(iteratePort(bool)));
    }
    m_deleteButton->setText("X");
    rowLayout->addWidget(m_deleteButton);

    m_parameterName->setEnabled(_port->getArgument().isVisible());
    m_showCheckbox-> setChecked(_port->getArgument().isVisible());

    connect(m_parameterName, SIGNAL(textEdited(QString)),     _port,           SLOT(fileNameChanged(QString)));
    connect(m_showCheckbox,  SIGNAL(toggled(bool)),           this ,           SLOT(showPort(bool)));
    connect(m_deleteButton,  SIGNAL(clicked(bool)),           this,            SLOT(removePort()));
    connect(_port,           SIGNAL(isConnected(bool)),       m_showCheckbox,  SLOT(setDisabled(bool)));
    connect(_port,           SIGNAL(changeFileName(QString)), m_parameterName, SLOT(setText(QString)));

    initialiseStyleSheets();
}

void PortRow::removePort(
        )
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, QString("Are you sure?"), QString("Are you sure you want to remove this port?"), QMessageBox::Yes | QMessageBox::No);
    switch(reply)
    {
    case QMessageBox::Yes :
        break;
    case QMessageBox::No :
        return;
    default :
        return;
    }

    m_port->removePort();
    disconnect(m_showCheckbox,  SIGNAL(toggled(bool)), this, SLOT(showPort(bool)));
    disconnect(m_deleteButton,  SIGNAL(toggled(bool)), this, SLOT(removePort()));
    m_parent->removeRow(this);
}

void PortRow::iteratePort(
        bool _iterator
        )
{
    m_port->setAsIterator(_iterator);
}

void PortRow::showPort(
        bool _visible
        )
{
    m_parameterName->setEnabled(_visible);
    m_port->toggleVisibility(_visible);
    if(!_visible && m_iterateCheckbox)
    {
        m_iterateCheckbox->setChecked(false);
        iteratePort(false);
    }
}

void PortRow::saveToJson(
        QJsonObject& o_json
        ) const
{
    o_json["value"]      = m_parameterName->text();
    o_json["inputPort"]  = QString::number((quint64) m_port->getInputPort(), 16);
    o_json["outputPort"] = QString::number((quint64) m_port->getOutputPort(), 16);
    o_json["visible"]    = m_showCheckbox->isChecked();
    o_json["iterator"]   = m_iterateCheckbox ? m_iterateCheckbox->isChecked() : false;
}

QString PortRow::getParameterName(
        ) const
{
    return m_parameterName->text();
}


void PortRow::initialiseStyleSheets(
        )
{
    QFile fileVisibility(":/qss/visibility_button.qss");
    fileVisibility.open(QFile::ReadOnly);
    QString styleSheetVisibility = QString::fromLatin1(fileVisibility.readAll());
    m_showCheckbox->setStyleSheet(styleSheetVisibility);

    if(m_iterateCheckbox)
    {
        QFile fileIterator(":/qss/iterator_button.qss");
        fileIterator.open(QFile::ReadOnly);
        QString styleSheetIterator = QString::fromLatin1(fileIterator.readAll());
        m_iterateCheckbox->setStyleSheet(styleSheetIterator);
    }
}

PortRow::~PortRow()
{
//    delete m_parameterName;
//    delete m_showCheckbox;
//    delete m_iterateCheckbox;
//    delete m_deleteButton;
}
