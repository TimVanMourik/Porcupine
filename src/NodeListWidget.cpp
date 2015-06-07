#include <QStandardItemModel>

#include "NodeListWidget.hpp"
#include "NodeTreeModel.hpp"

NodeListWidget::NodeListWidget(
        QWidget* _parent
        ) :
//    QTreeView(_parent)
    QWidget(_parent),
    m_layout(new QVBoxLayout(this))
{
    setLayout(m_layout);
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

void NodeListWidget::addNodeModel(
        )
{
    m_nodeTreeModels.append(new NodeTreeModel());
    m_layout->addWidget(m_nodeTreeModels.last());
    setModelAt(m_nodeTreeModels.length() - 1);
}

NodeTreeModel* NodeListWidget::modelAt(
        unsigned int _i
        )
{
    return m_nodeTreeModels[_i];
}

void NodeListWidget::setModelAt(
        int _i
        )
{
    for (int i = 0; i < m_layout->count(); ++i)
    {
        if(i == _i)
        {
            m_layout->itemAt(i)->widget()->setVisible(true);
        }
        else
        {
            m_layout->itemAt(i)->widget()->setVisible(false);
        }
    }
}

NodeListWidget::~NodeListWidget(
        )
{

}

