#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QGraphicsItem>
#include <QLinearGradient>
#include <QPen>

#include "Singleton.hpp"

class Preferences : public Singleton<Preferences>
{
    friend class Singleton<Preferences>;
public:
    void setSceneBackgroundBrush(
            const QBrush& _brush
            );

    void setNodeBrushUnselected(
            const QBrush& _brush
            );
    void setNodeBrushSelected(
            const QBrush& _brush
            );
    void setNodePenUnselected(
            const QPen& _pen
            );
    void setNodePenSelected(
            const QPen& _pen
            );

    void setLinkBrushUnselected(
            const QBrush& _brush
            );
    void setLinkBrushSelected(
            const QBrush& _brush
            );
    void setLinkPenUnselected(
            const QPen& _pen
            );
    void setLinkPenSelected(
            const QPen& _pen
            );

    void setPortBrushUnselected(
            const QBrush& _brush
            );
    void setPortBrushSelected(
            const QBrush& _brush
            );
    void setPortPenUnselected(
            const QPen& _pen
            );
    void setPortPenSelected(
            const QPen& _pen
            );

    void setPortTextColor(
            const QColor& _color
            );

    const QBrush& getSceneBackgroundBrush(
            ) const;

    const QBrush& getNodeBrushUnselected(
            ) const;
    const QBrush& getNodeBrushSelected(
            ) const;
    const QPen& getNodePenUnselected(
            ) const;
    const QPen& getNodePenSelected(
            ) const;

    const QBrush& getLinkBrushUnselected(
            ) const;
    const QBrush& getLinkBrushSelected(
            ) const;
    const QPen& getLinkPenUnselected(
            ) const;
    const QPen& getLinkPenSelected(
            ) const;

    const QBrush& getPortBrushUnselected(
            ) const;
    const QBrush& getPortBrushSelected(
            ) const;
    const QPen& getPortPenUnselected(
            ) const;
    const QPen& getPortPenSelected(
            ) const;
    const QColor& getPortTextColor(
            ) const;
private:
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
