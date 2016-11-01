#ifndef SELECTIONBOX_HPP
#define SELECTIONBOX_HPP

#include <QGraphicsPathItem>

class QDomElement;

class Node;
class Port;

class SelectionBox : public QGraphicsPathItem
{
public:
    //
    enum {
        Type = QGraphicsItem::UserType + 5
    };
    SelectionBox(
            const QPointF& _mousePosition,
            QGraphicsScene* _scene
            );
    //
    void paint(
            QPainter* _painter,
            const QStyleOptionGraphicsItem* _option,
            QWidget* _widget
            );
    //
    int type(
            ) const;
    //
    void reshape(
            const QPointF& _mousePosition
            );
    //
    void reshape(
            const qreal _x1,
            const qreal _y1,
            const qreal _x2,
            const qreal _y2
            );
    //
    void updateOpacity(
            float _scalingFactor
            );
    //
    void setNodeList(
            QList<Node*>& _nodeList
            );
    //
    void saveToXml(
            QDomElement& _xmlElement
            );
    //
    void loadFromXml(
            QDomElement& _xmlNode,
            QMap<quint64, Port*>& o_portMap
            );
    //
    ~SelectionBox(
            );
private:
    //
    static qreal s_rounding;
    //
    QPointF m_topLeftCorner;
    //
    QList<Node*> m_nodeList;
};

#endif // SELECTIONBOX_HPP
