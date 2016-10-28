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
