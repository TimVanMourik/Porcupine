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

#include <QLinearGradient>

#include "Preferences.hpp"

Preferences::Preferences() :
    Singleton()
{
    //Colour settings
    m_sceneBackgroundBrush = QBrush(QImage(":/images/RepeatingBrains.png"));

    QLinearGradient nodeGradient(0.0, 0.0, 0.0, 30);
    nodeGradient.setColorAt(1, QColor(110, 5, 0));
    nodeGradient.setColorAt(0, QColor(130, 5, 0));
    m_nodeBrushUnselected       = QBrush(nodeGradient);
    m_nodeBrushSelected         = QBrush(nodeGradient);
    m_nodePenUnselected         = QPen(QColor(20, 20, 20));
    m_nodePenSelected           = QPen(Qt::red);

    QLinearGradient postitGradient(0.0, 0.0, 0.0, 30);
    postitGradient.setColorAt(1, QColor(240, 240, 0));
    postitGradient.setColorAt(0, QColor(220, 220, 0));
    m_postitBrushUnselected     = QBrush(postitGradient);
    m_postitBrushSelected       = QBrush(postitGradient);
    m_postitPenUnselected       = QPen(QColor(60, 60, 0));
    m_postitPenSelected         = QPen(QColor(140, 140, 20));

    m_linkBrushUnselected       = QBrush(Qt::NoBrush);
    m_linkBrushSelected         = QBrush(Qt::NoBrush);
    m_linkPenUnselected         = QPen(QColor(170, 110, 110), 2);
    m_linkPenSelected           = QPen(QColor(110, 110, 170), 2);

    m_portBrushUnselected       = QColor(213, 74, 67);
    m_portBrushSelected         = QColor(160, 200, 160);
    m_portPenUnselected         = QPen(QColor(200, 130, 130));
    m_portPenSelected           = QPen(QColor(130, 130, 200));

    m_portTextColor             = QColor(230, 230, 230);

    m_selectionBrushUnselected  = QBrush(nodeGradient);
    m_selectionBrushSelected    = QBrush(nodeGradient);
    m_selectionPenUnselected    = QPen(QColor(170, 170, 240), 2);
    m_selectionPenSelected      = QPen(QColor(20, 20, 40), 2);
    m_selectionOpacity          = 0.1;

    //sizes
    m_nodeHorizontalMargin      = 20;
    m_nodeVerticalMargin        = 10;
    m_nodeWidth                 = m_nodeHorizontalMargin;
    m_nodeHeight                = m_nodeVerticalMargin;
    m_nodeTextSpacing           = 3;
}

Preferences::~Preferences()
{
}

