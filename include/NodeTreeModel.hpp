#ifndef NODETREEMODEL_H
#define NODETREEMODEL_H

#include <QStandardItemModel>
#include <QWidget>

class Node;
class QVBoxLayout;
//class NodeTreeModel : public QStandardItemModel
class NodeTreeModel : public QWidget
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
private:
    //
    QVBoxLayout* m_layout;
    //
//    QVector<const Node*> m_nodes;
};

#endif // NODETREEMODEL_H
