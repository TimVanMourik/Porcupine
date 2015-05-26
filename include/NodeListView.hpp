#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QListView>
#include <QTreeView>
#include <QVBoxLayout>
#include <QVector>

class NodeTreeModel;

//class NodeListView : public QTreeView
class NodeListView : public QWidget
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
//    void dropEvent(
//            QDropEvent* _event
//            );
    //
    ~NodeListView(
            );

private:
    QVector<NodeTreeModel*> m_nodeTreeModels;
    int m_current;
};

#endif // TREEVIEW_H
