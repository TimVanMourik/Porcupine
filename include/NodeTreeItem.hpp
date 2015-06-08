#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QStandardItem>
#include <QWidget>

class Node;
class PortPair;
class QVBoxLayout;

class NodeTreeItem : public QWidget
{
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
    ~NodeTreeItem(
            );
private:
    //
    QVBoxLayout* m_layout;
    //
    const Node* m_node;
    //
    QMap<QStandardItem*, PortPair*> m_ports;
};

#endif // NODETREEITEM_H
