#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QStandardItemModel>

#include <Node.hpp>

class NodeTreeModel : public QStandardItemModel
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
    ~NodeTreeModel(
            );
public slots:
    //
    void fileNameFieldChanged(
            QStandardItem* _item
            );
};

#endif // NODETREEITEM_H
