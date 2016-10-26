#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>

#include "Preferences.hpp"
#include "SelectionBox.hpp"

SelectionBox::SelectionBox(
        const QPointF& _mousePosition,
        QGraphicsScene* _scene
        ) :
    m_topLeftCorner(_mousePosition)
{
    _scene->addItem(this);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    reshape(m_topLeftCorner);
}

void SelectionBox::paint(
        QPainter* _painter,
        const QStyleOptionGraphicsItem* _option,
        QWidget* _widget
        )
{
    Q_UNUSED(_painter);
    Q_UNUSED(_option);
    Q_UNUSED(_widget);

    Preferences& preferences = Preferences::getInstance();
    _painter->setPen(preferences.m_selectionPenUnselected);
    _painter->setBrush(preferences.m_selectionBrushUnselected);
    _painter->setOpacity(preferences.m_selectionOpacity);
//    if(isSelected())
//    {
//        _painter->setPen(preferences.getLinkPenSelected());
//        _painter->setBrush(preferences.getLinkBrushSelected());
//    }
//    else
//    {
//        _painter->setPen(preferences.getLinkPenUnselected());
//        _painter->setBrush(preferences.getLinkBrushUnselected());
//    }
    _painter->drawPath(path());
}

int SelectionBox::type(
        ) const
{
    return Type;
}

void SelectionBox::reshape(
        const QPointF& _mousePosition
        )
{
    QPainterPath path;
    path.addRect(QRect((int)m_topLeftCorner.x(),(int) m_topLeftCorner.y(), _mousePosition.x() - m_topLeftCorner.x(), _mousePosition.y() - m_topLeftCorner.y()));
    setPath(path);
}

void SelectionBox::reshape(
        const qreal _x1,
        const qreal _y1,
        const qreal _x2,
        const qreal _y2
        )
{
    QPainterPath path;
    path.addRect(_x1, _y1, _x2, _y2);
    setPath(path);
}

void SelectionBox::saveToXml(
        QDomElement& _xmlElement
        )
{
    Q_UNUSED(_xmlElement);
}

void SelectionBox::loadFromXml(
        QDomElement& _xmlNode,
        QMap<quint64, Port*>& o_portMap
        )
{
    Q_UNUSED(_xmlNode);
    Q_UNUSED(o_portMap);
}

SelectionBox::~SelectionBox()
{
}
