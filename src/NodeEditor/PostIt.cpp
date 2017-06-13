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

//#include <assert.h>

//#include <QDomDocument>
//#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
//#include <QGraphicsScene>
#include <QLineEdit>
//#include <QLinearGradient>

//#include "Argument.hpp"
#include "PostIt.hpp"
#include "NodeEditor.hpp"
//#include "NodeLibrary.hpp"
//#include "NodeSetting.hpp"
#include "Preferences.hpp"
//#include "PortPair.hpp"

qreal PostIt::s_horizontalMargin  = 5;
qreal PostIt::s_verticalMargin    = 3;
qreal PostIt::s_textSpacing       = 1;

#include <iostream>
PostIt::PostIt(
        NodeEditor* _editor
        ) :
    QGraphicsPathItem(0),
    m_nameLabel(new QLineEdit())
{
    _editor->scene()->addItem(this);
    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(m_nameLabel);

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);
    m_nameLabel->setPalette(palette);
    m_nameLabel->setStyleSheet("* {background-color: rgba(0, 0, 0, 0);}");
    QFont font(scene()->font());
    font.setBold(true);
    m_nameLabel->setFont(font);
    m_nameLabel->setText("I am a post-it!");
    m_nameLabel->setFrame(false);
    m_nameLabel->setAttribute(Qt::WA_TranslucentBackground);

    m_nameLabel->move(-m_nameLabel->fontMetrics().width(m_nameLabel->text()) / 2, 0);
    QPainterPath path;
    path.addRect(-60, 0, 120, 120);
    setPath(path);
    setPen(QPen(Qt::darkRed));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

//    m_nameLabel->connect((QObject*) m_nameLabel, SIGNAL(textChanged(QString)), (QObject*) &m_antenna, SLOT(catchLabelChanged(QString)));
}

void PostIt::paint(
        QPainter* _painter,
        const QStyleOptionGraphicsItem* _option,
        QWidget* _widget
        )
{
    Q_UNUSED(_option);
    Q_UNUSED(_widget);

    Preferences& preferences = Preferences::getInstance();
    if(isSelected())
    {
        _painter->setPen(preferences.m_postitPenSelected);
        _painter->setBrush(preferences.m_postitBrushSelected);
    }
    else
    {
        _painter->setPen(preferences.m_postitPenUnselected);
        _painter->setBrush(preferences.m_postitBrushUnselected);
    }
    _painter->drawPath(path());
}

int PostIt::type(
        ) const
{
    return Type;
}

//void PostIt::loadFromXml(
//        QDomElement& _xmlNode,
//        QMap<quint64, Port*>& o_portMap
//        )
//{
//}

PostIt::~PostIt()
{
}
