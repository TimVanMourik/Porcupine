#include <QDropEvent>
#include <QMimeData>
#include <QVBoxLayout>

#include "NodeTreeItem.hpp"
#include "NodeTreeModel.hpp"

NodeTreeModel::NodeTreeModel(
        ) :
    QFrame(),
    m_layout(new QVBoxLayout())
{
    m_layout->setAlignment(Qt::AlignTop);

    setFrameShadow(QFrame::Raised);
    setFrameStyle(QFrame::StyledPanel);
    setLayout(m_layout);
//    setAcceptDrops(true);
}

void NodeTreeModel::addNode(
        const Node* _node
        )
{
    m_nodes.append(_node);
    NodeTreeItem* item = new NodeTreeItem(_node, this);
    m_layout->addWidget(item);
    m_nodeList.append(item);
    item->setNumber(m_nodeList.length());
    connect(item, SIGNAL(moved(NodeTreeItem*)), this, SLOT(nodeMoved(NodeTreeItem*)));
}

void NodeTreeModel::removeNode(
        const Node* _node
        )
{
    Q_UNUSED(_node)
//    for(int i = 0; i < rowCount(); ++i)
//    {
//        if(((NodeTreeItem*) item(i))->hasNode(_node))
//        {
//            removeRow(i);
//            break;
//        }
//    }
}

void NodeTreeModel::nodeMoved(
        NodeTreeItem* _item
        )
{
    m_nodeList.removeOne(_item);
    m_layout->removeWidget(_item);
    int index = m_nodeList.length() + 1;
    for(int i = 0; i < m_nodeList.length(); ++i)
    {
        if(m_nodeList[i]->y() > _item->y())
        {
            index = i;
            break;
        }
    }
    m_nodeList.insert(index, _item);
    m_layout->insertWidget(index, _item);

    updateNodeOrder();
}

void NodeTreeModel::updateNodeOrder(
        )
{
    for(int i = 0; i < m_nodeList.length(); ++i)
    {
        m_nodeList[i]->setNumber(i + 1);
    }
}

//#include <iostream>
//void NodeTreeModel::dragEnterEvent(
//        QDropEvent* _event
//        )
//{
//    std::cerr << _event->mimeData()->text().toStdString() << " A\n";
//    _event->acceptProposedAction();
//}

//void NodeTreeModel::dropEvent(
//        QDropEvent* _event
//        )
//{
//    std::cerr << _event->mimeData()->text().toStdString() << " B\n";
//}

NodeTreeModel::~NodeTreeModel(
        )
{
//    delete all items;
}

