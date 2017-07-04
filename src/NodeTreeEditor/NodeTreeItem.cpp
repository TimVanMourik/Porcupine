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

//#include <QApplication>
#include <QComboBox>
#include <QDrag>
#include <QDebug>
#include <QInputDialog>
#include <QDropEvent>
#include <QFormLayout>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

#include <QMimeData>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

#include "Node.hpp"
#include "NodeTreeItem.hpp"
#include "PortPair.hpp"
#include "PortBlock.hpp"

NodeTreeItem::NodeTreeItem(
        Node* _node,
        QWidget* _parent
        ) :
    QFrame(_parent),
    m_node(_node),
    m_startPosition(QPoint()),
    m_numberLabel(0),
    m_number(0),
    m_isSelected(false),
    m_portBlockLayout(0)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QWidget* headerBlock = new QWidget();
    QWidget* portBlock = new QWidget();
    mainLayout->addWidget(headerBlock);
    mainLayout->addWidget(portBlock);
    QHBoxLayout* headerLayout = new QHBoxLayout(headerBlock);
    m_portBlockLayout = new PortBlock(portBlock);

    setFrameShadow(QFrame::Raised);
    setFrameStyle(QFrame::StyledPanel);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, palette.window().color().darker(110));
    setAutoFillBackground(true);
    setPalette(palette);
    show();

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(2, 2, 2, 2);
    headerLayout->setSpacing(0);
    headerLayout->setContentsMargins(10, 10, 20, 0);

    // headerLayout
    m_numberLabel   = new QLabel(QString::number(m_number));
    QLabel* nameTag = new QLabel(m_node->getName());
    connect(&m_node->getAntenna(), SIGNAL(nodeNameChanged(QString)), nameTag, SLOT(setText(QString)));

    QPushButton* visibilityButton = new QPushButton();
    visibilityButton->setMaximumWidth(30);
    visibilityButton->setText("\\/");
    visibilityButton->setCheckable(true);

    headerLayout->addWidget(m_numberLabel);
    headerLayout->addWidget(nameTag);
    headerLayout->addWidget(visibilityButton);

    portBlock->setVisible(false);

    m_portBlockLayout->addPortBlock(m_node->getPorts());

    QPushButton* addPortButton = new QPushButton("Add port");
    m_portBlockLayout->addWidget(addPortButton);

    connect(addPortButton, SIGNAL(clicked(bool)), this, SLOT(addPort()));
    connect(visibilityButton, SIGNAL(toggled(bool)), portBlock, SLOT(setVisible(bool)));
    connect(&m_node->getAntenna(), SIGNAL(nodeSelected(bool)), this, SLOT(setSelected(bool)));
}

void NodeTreeItem::addPort()
{
    Argument portArgument;
    portArgument.setVisible(true);
    portArgument.setIterator(false);
    portArgument.setEditable(true);
    QString portTitle = QInputDialog::getText(this, "Port name", "Please enter the port name");
    if(portTitle.isEmpty())
    {
        return;
    }
    portArgument.setName(portTitle);

    QMessageBox ioBox;
    ioBox.setText(tr("Do you want an input or output port?"));
    QAbstractButton* input  = ioBox.addButton(tr("Input"),  QMessageBox::YesRole);
    QAbstractButton* output = ioBox.addButton(tr("Output"), QMessageBox::NoRole);
    ioBox.exec();

    Argument title(m_node->getJson()["title"].toObject());
    if(ioBox.clickedButton() == input)
    {
        portArgument.setInput(true);
        portArgument.setOutput(false);
        QList<QString> languages = title.getLanguages();
        foreach (QString language, languages)
        {
            portArgument.addCode(language, portTitle);
        }
    }
    else if(ioBox.clickedButton() == output)
    {
        portArgument.setInput(false);
        portArgument.setOutput(true);
    }
    else
    {
        return;
    }
    PortPair* p = m_node->addPortPair(portArgument, false);
    m_node->repositionPorts();
    m_portBlockLayout->addPortRow(p);
}

const QVector<PortPair*> NodeTreeItem::getPorts(
        ) const
{
    return m_node->getPorts();
}

QString NodeTreeItem::getParameterName(
        const QString& _portName
        ) const
{
    return m_portBlockLayout->getParameterName(_portName);
}

bool NodeTreeItem::isAncestorOf(
        NodeTreeItem* _item
        )
{
    return _item->getNode()->hasAncestor(m_node);
}

const Node* NodeTreeItem::getNode(
        ) const
{
    return m_node;
}

const QJsonObject& NodeTreeItem::getJson(
        ) const
{
    return m_node->getJson();
}

QVector<const Node*> NodeTreeItem::getDescendants(
        )
{
    return m_node->getDescendants();
}

void NodeTreeItem::saveToJson(
        QJsonObject& o_json
        ) const
{
    o_json = m_node->getJson();
    QJsonArray position;
    position.append(m_node->pos().x());
    position.append(m_node->pos().y());
    o_json["position"] = position;

//    qDebug() << "Save port block";
    m_portBlockLayout->saveToJson(o_json);
}

void NodeTreeItem::mousePressEvent(
        QMouseEvent* _event
        )
{
//    if(m_isSelected)
//    {
//       setSelected(false);
//    }
//    else
//    {
//        setSelected(true);
//    }
    raise();
//    setWindowOpacity(0.5);
    if(_event->button() == Qt::LeftButton)
    {
        m_startPosition = _event->globalPos();
    }
}

void NodeTreeItem::mouseMoveEvent(
        QMouseEvent* _event
        )
{
    const QPoint delta = _event->globalPos() - m_startPosition;
    move(x(), y() + delta.y());
    m_startPosition = _event->globalPos();
}

void NodeTreeItem::mouseReleaseEvent(
        QMouseEvent* _event
        )
{
    Q_UNUSED(_event);
//    setWindowOpacity(1);
    emit moved(this);
}

void NodeTreeItem::setNumber(
        unsigned int _i
        )
{
    m_number = _i;
    m_numberLabel->setText(QString::number(m_number));
}


void NodeTreeItem::setSelected(
        bool _isSelected
        )
{
    m_isSelected = _isSelected;
    if(_isSelected)
    {
        setObjectName("myObject");
        setStyleSheet("#myObject {border: 2px solid black;}");
    }
    else
    {
        setStyleSheet("");
    }
}

NodeTreeItem::~NodeTreeItem(
        )
{
}

