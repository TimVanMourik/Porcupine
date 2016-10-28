#include <QLinearGradient>

#include "Preferences.hpp"

Preferences::Preferences() :
    Singleton()
{
    //Colour settings
    m_sceneBackgroundBrush = QBrush(QImage(":/Images/RepeatingBrains.png"));

    QLinearGradient gradient(0.0, 0.0, 0.0, 30);
    gradient.setColorAt(1, QColor(130, 5, 0));
    gradient.setColorAt(0, QColor(110, 5, 0));

    m_nodeBrushUnselected       = QBrush(gradient);
    m_nodeBrushSelected         = QBrush(gradient);
    m_nodePenUnselected         = QPen(QColor(20, 20, 20));
    m_nodePenSelected           = QPen(Qt::red);

    m_linkBrushUnselected       = QBrush(Qt::NoBrush);
    m_linkBrushSelected         = QBrush(Qt::NoBrush);
    m_linkPenUnselected         = QPen(QColor(170, 110, 110), 2);
    m_linkPenSelected           = QPen(QColor(110, 110, 170), 2);

    m_portBrushUnselected       = QColor(213, 74, 67);
    m_portBrushSelected         = QColor(160, 200, 160);
    m_portPenUnselected         = QPen(QColor(200, 130, 130));
    m_portPenSelected           = QPen(QColor(130, 130, 200));

    m_portTextColor             = QColor(230, 230, 230);

    m_selectionBrushUnselected  = QBrush(gradient);
    m_selectionBrushSelected    = QBrush(gradient);
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

