#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QVector>

class NodeTreeModel;

class NodeListView : public QTreeView
{
public:
    //
    NodeListView(
            QWidget* _parent = 0
            );
    //
    void addNodeModel(
            );
    //
    NodeTreeModel* modelAt(
            unsigned int _i
            );
    //
    void setModelAt(
            int _i
            );
    //
    ~NodeListView(
            );

private:
    QVector<NodeTreeModel*> m_nodeTreeModels;
};

#endif // TREEVIEW_H
