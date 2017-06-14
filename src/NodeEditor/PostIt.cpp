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

#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QTextEdit>

#include "PostIt.hpp"
#include "NodeEditor.hpp"
#include "Preferences.hpp"

qreal PostIt::s_horizontalMargin  = 5;
qreal PostIt::s_verticalMargin    = 3;
qreal PostIt::s_textSpacing       = 1;

#include <iostream>
PostIt::PostIt(
        NodeEditor* _editor
        ) :
    QGraphicsPathItem(0),
    m_nameLabel(new QLineEdit()),
    m_text(new QTextEdit())
{
    int width  = 160;
    int height = 160;
    QPainterPath path;
    path.addRect(-width / 2, 0, width, height);
    setPath(path);
    setPen(QPen(Qt::darkRed));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    _editor->scene()->addItem(this);
    QGraphicsProxyWidget* proxyLabel = new QGraphicsProxyWidget(this);
    proxyLabel->setWidget(m_nameLabel);
    QGraphicsProxyWidget* proxyText = new QGraphicsProxyWidget(this);
    proxyText->setWidget(m_text);

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);
    QFont font(scene()->font());
    font.setBold(true);
    m_nameLabel->setFont(font);
    m_nameLabel->setPalette(palette);
    m_nameLabel->setStyleSheet("* {background-color: rgba(0, 0, 0, 0);}");
    m_nameLabel->setText("I am a porcupost-it!");
    m_nameLabel->setFrame(false);
    m_nameLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_nameLabel->move(-m_nameLabel->fontMetrics().width(m_nameLabel->text()) / 2, 0);

    m_text->setPlaceholderText("Text");
    m_text->setPalette(palette);
    m_text->setStyleSheet("* {background-color: rgba(0, 0, 0, 0);}");
    m_text->setAttribute(Qt::WA_TranslucentBackground);
    m_text->move(-width / 2 + s_horizontalMargin, m_nameLabel->fontMetrics().height() * 1.5);
    m_text->setMaximumWidth(width - 2 * s_horizontalMargin);
    m_text->setMaximumHeight(height - 2 * s_verticalMargin - m_nameLabel->fontMetrics().height() * 1.5);
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
    delete m_nameLabel;
    delete m_text;
}
