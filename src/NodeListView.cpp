#include <QStandardItemModel>

#include "NodeListView.hpp"
#include "NodeTreeModel.hpp"

NodeListView::NodeListView(
        QWidget* _parent
        ) :
    QTreeView(_parent)
{
}

void NodeListView::addNodeModel(
        )
{
    m_nodeTreeModels.append(new NodeTreeModel());
    this->setModel(m_nodeTreeModels.last());
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
    this->setModel(m_nodeTreeModels[_i]);
}

NodeListView::~NodeListView(
        )
{

}

