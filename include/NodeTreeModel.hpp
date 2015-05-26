#ifndef NODETREEMODEL_H
#define NODETREEMODEL_H

#include <QStandardItemModel>
#include <QVBoxLayout>

class Node;

//class NodeTreeModel : public QStandardItemModel
class NodeTreeModel : public QVBoxLayout
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
    ~NodeTreeModel(
            );
public slots:
    //
    void fileNameFieldChanged(
            QStandardItem* _item
            );
//private:
    //
//    QVector<const Node*> m_nodes;
};

#endif // NODETREEMODEL_H
