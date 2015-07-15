#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QPoint>
#include <QStandardItem>
#include <QFrame>

class Node;
class NodeSetting;
class PortPair;
class QLabel;
class QLineEdit;
class QVBoxLayout;

class NodeTreeItem : public QFrame
{
    Q_OBJECT
public:
    ///@todo make sure that the item doesn't flash before moving to the right position
    NodeTreeItem(
            const Node* _node,
            QWidget* _parent
            );
    //
    void setPort(
            PortPair* _port
            );
    //
    bool isAncestorOf(
            NodeTreeItem* _item
            );
    //
    const Node* getNode(
            ) const;
    //
    const NodeSetting* getNodeSetting(
            ) const;
    //
    QVector<const Node*> getDescendants(
            );
    //
//    bool hasNode(
//            const Node* _node
//            );
    //
    void setNumber(
            unsigned int _i
            );
    //
    const QString& getFileName(
            const QString& _portName
            ) const;
    //
    void mousePressEvent(
            QMouseEvent* _event
            );
    //
    void mouseMoveEvent(
            QMouseEvent* _event
            );
    //
    void mouseReleaseEvent(
            QMouseEvent* _event
            );
    //
    virtual ~NodeTreeItem(
            );
signals:
    void moved(
            NodeTreeItem* _item
            );
private:
    //
    const Node* m_node;
    //
    QWidget* m_portBlock;
    //
    QMap<QWidget*, PortPair*> m_ports;
    //
    QMap<QString, QLineEdit*> m_fileNames;
    //
    QPoint m_position;
    //
    QLabel* m_numberLabel;
    //
    unsigned int m_number;
};

#endif // NODETREEITEM_H
