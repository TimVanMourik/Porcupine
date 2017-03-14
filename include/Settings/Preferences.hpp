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

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QGraphicsItem>
#include <QPen>

#include "Singleton.hpp"

class Preferences : public Singleton<Preferences>
{
    friend class Singleton<Preferences>;
public:
//Let's make these public. Otherwise we're flooded with getters and setters
    QBrush m_sceneBackgroundBrush;

    QBrush m_nodeBrushUnselected;
    QBrush m_nodeBrushSelected;
    QPen m_nodePenUnselected;
    QPen m_nodePenSelected;

    QBrush m_linkBrushUnselected;
    QBrush m_linkBrushSelected;
    QPen m_linkPenUnselected;
    QPen m_linkPenSelected;

    QBrush m_portBrushUnselected;
    QBrush m_portBrushSelected;
    QPen m_portPenUnselected;
    QPen m_portPenSelected;

    QBrush m_selectionBrushUnselected;
    QBrush m_selectionBrushSelected;
    QPen m_selectionPenUnselected;
    QPen m_selectionPenSelected;
    qreal m_selectionOpacity;

    QColor m_portTextColor;

    qreal m_nodeWidth;
    qreal m_nodeHeight;
    qreal m_nodeHorizontalMargin;
    qreal m_nodeVerticalMargin;
    qreal m_nodeTextSpacing;

    Preferences(
            );
    /// @brief
    Preferences(
            Preferences const& _copy
            ); //Not implemented
    /// @brief
    Preferences& operator=(
            Preferences const& _copy
            ); //Not implemented
    /// @brief
    ~Preferences(
            );
};

#endif // PREFERENCES_H
