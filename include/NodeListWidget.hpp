#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QListView>
#include <QTreeView>
#include <QVBoxLayout>
#include <QVector>

class NodeTreeEditor;
class QScrollArea;

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
    NodeTreeEditor* modelAt(
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
//    QScrollArea* m_scrollArea;
    //
    QVector<NodeTreeEditor*> m_nodeTreeModels;
};

#endif // TREEVIEW_H
