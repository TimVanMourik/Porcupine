#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QStandardItemModel>

#include <Node.hpp>

class NodeTreeModel : public QStandardItemModel
{
public:
    //
    NodeTreeModel(
            );
    //
    void addNode(
            const Node* _node
            );
    //
    ~NodeTreeModel(
            );
};

#endif // NODETREEITEM_H
