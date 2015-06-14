#include <QScrollArea>
#include <QStandardItemModel>

#include "NodeListWidget.hpp"
#include "NodeTreeModel.hpp"

NodeListWidget::NodeListWidget(
        QWidget* _parent
        ) :
    QWidget(_parent),
    m_layout(new QVBoxLayout(this))//,
//    m_scrollArea(new QScrollArea(this))
{
    setLayout(m_layout);
}

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
//    m_scrollArea->setWidget(m_nodeTreeModels[_i]);
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
    delete m_layout;
    foreach (NodeTreeModel* model, m_nodeTreeModels)
    {
        delete model;
    }
}

