#ifndef NODETREEMODEL_H
#define NODETREEMODEL_H

#include <QStandardItemModel>
#include <QFrame>

class Node;
class NodeTreeItem;
class QVBoxLayout;

class NodeTreeModel : public QFrame
{
    Q_OBJECT
public:
    //
    NodeTreeModel(
            );
    //
    void addNode(
            const Node* _node
            );
    //
    void removeNode(
            const Node* _node
            );
    //
    void updateNodeOrder(
            );
    //
    ~NodeTreeModel(
            );
public slots:
    /// @brief receives signal that _item just swapped places, so the nodes need to be reordered.
    void nodeMoved(
            NodeTreeItem* _item
            );
    /// @when a new link is created, the node list needs to be checkd for correctness and perhaps restructured
    void linkCreated(
            const Node* _from,
            const Node* _to
            );
private:
    //
    QVBoxLayout* m_layout;
    //
    QVector<const Node*> m_nodes;
    //
    QList<NodeTreeItem*> m_nodeList;
};

#endif // NODETREEMODEL_H
