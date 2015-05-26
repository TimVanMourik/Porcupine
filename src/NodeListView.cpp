#include <QStandardItemModel>

#include "NodeListView.hpp"
#include "NodeTreeModel.hpp"

NodeListView::NodeListView(
        QWidget* _parent
        ) :
//    QTreeView(_parent)
    QWidget(_parent),
    m_current(0)
{
//    setDragEnabled(true);
//    viewport()->setAcceptDrops(true);
//    setDropIndicatorShown(true);
//    setDefaultDropAction(Qt::MoveAction);
//    setDragDropMode(QAbstractItemView::DragOnly);
}

#include <iostream>
#include <QDropEvent>
#include <QMimeData>
//void NodeListView::dropEvent(
//        QDropEvent* _event
//        )
//{
//    // if there is a horizontal drag:
//    std::cerr << _event->mimeData()->dynamicPropertyNames().length() << "\n";
//    if(true)
//    {
//        QListView::dropEvent(_event);
//    }
//    else
//    {
//        _event->ignore();
//    }
//}

void NodeListView::addNodeModel(
        )
{
    m_nodeTreeModels.append(new NodeTreeModel());
//    this->setModel(m_nodeTreeModels.last());
//    removeItem();
    m_current = m_nodeTreeModels.length() - 1;
    setLayout(m_nodeTreeModels[m_current]);
}

NodeTreeModel* NodeListView::modelAt(
        unsigned int _i
        )
{
    return m_nodeTreeModels[_i];
}

void NodeListView::setModelAt(
        int _i
        )
{
    setLayout(m_nodeTreeModels[_i]);
//    removeItem(m_nodeTreeModels[m_current]);
//    m_current = _i;
//    addItem(m_nodeTreeModels[m_current]);
}

NodeListView::~NodeListView(
        )
{

}

