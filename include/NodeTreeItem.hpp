#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QPoint>
#include <QStandardItem>
#include <QWidget>

class Node;
class PortPair;
class QVBoxLayout;

class NodeTreeItem : public QWidget
{
    Q_OBJECT
public:
    //
    NodeTreeItem(
            const Node* _node
            );
    //
    void setPort(
            PortPair* _port
            );
    //
    void setHasFilName(
            QStandardItem* _item,
            bool _hasFileName
            );
    //
    bool hasNode(
            const Node* _node
            );
    //
//    void paintEvent(
//            QPaintEvent* _event
//            );
    //
    void mousePressEvent(
            QMouseEvent* _event
            );
    //
    void mouseMoveEvent(
            QMouseEvent* _event
            );
    //
    ~NodeTreeItem(
            );
//public slots:
//    //
//    void setPortsVisible(
//            bool _visibility
//            );
private:
    //
    const Node* m_node;
    //
    QWidget* m_portBlock;
    //
    QMap<QWidget*, PortPair*> m_ports;
    //
    QPoint m_dragStartPosition;
};

#endif // NODETREEITEM_H
