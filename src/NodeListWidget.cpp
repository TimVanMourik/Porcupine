#include <QStandardItemModel>

#include "NodeListWidget.hpp"
#include "NodeTreeModel.hpp"

NodeListWidget::NodeListWidget(
        QWidget* _parent
        ) :
//    QTreeView(_parent)
    QWidget(_parent),
    m_layout(new QVBoxLayout(this)),
    m_currentModel(0)
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
    setModelAt(m_nodeTreeModels.length() - 1);
//    setModel(m_nodeTreeModels.last());
//    removeItem();
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
    std::cerr << m_nodeTreeModels[m_currentModel] << "\n";
//    m_layout->removeWidget((QWidget*) m_nodeTreeModels[m_currentModel]);
//    m_currentModel = _i;
    m_layout->addWidget((QWidget*) m_nodeTreeModels[m_currentModel]);

    m_layout->replaceWidget(m_nodeTreeModels[m_currentModel], m_nodeTreeModels[_i]);
    m_currentModel = _i;
//    setLayout(m_nodeTreeModels[_i]);
//    removeItem(m_nodeTreeModels[m_current]);
//    m_current = _i;
//    addItem(m_nodeTreeModels[m_current]);
}

NodeListWidget::~NodeListWidget(
        )
{

}

