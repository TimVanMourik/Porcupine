#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QListView>
#include <QTreeView>
#include <QVBoxLayout>
#include <QVector>

class NodeTreeModel;

//class NodeListView : public QTreeView
class NodeListWidget : public QWidget
{
public:
    //
    NodeListWidget(
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
    ~NodeListWidget(
            );

private:
    //
    QVBoxLayout* m_layout;
    //
    QVector<NodeTreeModel*> m_nodeTreeModels;
    //
    int m_currentModel;
};

#endif // TREEVIEW_H
