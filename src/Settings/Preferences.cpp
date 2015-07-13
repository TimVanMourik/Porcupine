#include <QGraphicsItem>
#include <QLinearGradient>

#include "Preferences.hpp"

Preferences::Preferences() :
    Singleton()
{
    //Colour settings

//    m_sceneBackgroundBrush = QBrush(QColor(50, 50, 50), Qt::Dense7Pattern);
    m_sceneBackgroundBrush = QBrush(QColor(50, 50, 50), Qt::SolidPattern);

    QLinearGradient gradient(0.0, 0.0, 0.0, 30);
    gradient.setColorAt(1, QColor(130, 5, 0));
    gradient.setColorAt(0, QColor(110, 5, 0));

    m_nodeBrushUnselected = QBrush(gradient);
    m_nodeBrushSelected   = QBrush(gradient);
    m_nodePenUnselected   = QPen(QColor(20, 20, 20));
    m_nodePenSelected     = QPen(Qt::red);

    m_linkBrushUnselected = QBrush(Qt::NoBrush);
    m_linkBrushSelected   = QBrush(Qt::NoBrush);
    m_linkPenUnselected   = QPen(QColor(170, 110, 110), 2);
    m_linkPenSelected     = QPen(QColor(110, 110, 170), 2);

    m_portBrushUnselected = QColor(213, 74, 67);
    m_portBrushSelected   = QColor(160, 200, 160);
    m_portPenUnselected   = QPen(QColor(200, 130, 130));
    m_portPenSelected     = QPen(QColor(130, 130, 200));

    m_portTextColor       = QColor(230, 230, 230);

    //sizes
    m_nodeHorizontalMargin  = 20;
    m_nodeVerticalMargin    = 10;
    m_nodeWidth             = m_nodeHorizontalMargin;
    m_nodeHeight            = m_nodeVerticalMargin;
    m_nodeTextSpacing       = 3;
}


void Preferences::setSceneBackgroundBrush(
        const QBrush& _brush
        )
{
    m_sceneBackgroundBrush = _brush;
}

void Preferences::setNodeBrushUnselected(
        const QBrush& _brush
        )
{
    m_nodeBrushUnselected = _brush;
}

void Preferences::setNodeBrushSelected(
        const QBrush& _brush
        )
{
    m_nodeBrushSelected = _brush;
}

void Preferences::setNodePenUnselected(
        const QPen& _pen
        )
{
    m_nodePenUnselected = _pen;
}

void Preferences::setNodePenSelected(
        const QPen& _pen
        )
{
    m_nodePenSelected = _pen;
}


void Preferences::setLinkBrushUnselected(
        const QBrush& _brush
        )
{
    m_linkBrushUnselected = _brush;
}

void Preferences::setLinkBrushSelected(
        const QBrush& _brush
        )
{
    m_linkBrushSelected = _brush;
}

void Preferences::setLinkPenUnselected(
        const QPen& _pen
        )
{
    m_linkPenUnselected = _pen;
}

void Preferences::setLinkPenSelected(
        const QPen& _pen
        )
{
    m_linkPenSelected = _pen;
}


void Preferences::setPortBrushUnselected(
        const QBrush& _brush
        )
{
    m_portBrushUnselected = _brush;
}

void Preferences::setPortBrushSelected(
        const QBrush& _brush
        )
{
    m_portBrushSelected = _brush;
}

void Preferences::setPortPenUnselected(
        const QPen& _pen
        )
{
    m_portPenUnselected = _pen;
}

void Preferences::setPortPenSelected(
        const QPen& _pen
        )
{
    m_portPenSelected = _pen;
}

void Preferences::setPortTextColor(
        const QColor& _color
        )
{
    m_portTextColor = _color;
}


const QBrush& Preferences::getSceneBackgroundBrush(
        ) const
{
    return m_sceneBackgroundBrush;
}
const QBrush& Preferences::getNodeBrushUnselected(
        ) const
{
    return m_nodeBrushUnselected;
}

const QBrush& Preferences::getNodeBrushSelected(
        ) const
{
    return m_nodeBrushSelected;
}

const QPen& Preferences::getNodePenUnselected(
        ) const
{
    return m_nodePenUnselected;
}

const QPen& Preferences::getNodePenSelected(
        ) const
{
    return m_nodePenSelected;
}


const QBrush& Preferences::getLinkBrushUnselected(
        ) const
{
    return m_linkBrushUnselected;
}

const QBrush& Preferences::getLinkBrushSelected(
        ) const
{
    return m_linkBrushSelected;
}

const QPen& Preferences::getLinkPenUnselected(
        ) const
{
    return m_linkPenUnselected;
}

const QPen& Preferences::getLinkPenSelected(
        ) const
{
    return m_linkPenSelected;
}


const QBrush& Preferences::getPortBrushUnselected(
        ) const
{
    return m_portBrushUnselected;
}

const QBrush& Preferences::getPortBrushSelected(
        ) const
{
    return m_portBrushSelected;
}

const QPen& Preferences::getPortPenUnselected(
        ) const
{
    return m_portPenUnselected;
}

const QPen& Preferences::getPortPenSelected(
        ) const
{
    return m_portPenSelected;
}

const QColor& Preferences::getPortTextColor(
        ) const
{
    return m_portTextColor;
}

Preferences::~Preferences()
{
}

