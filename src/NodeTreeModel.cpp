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
//    connect
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
    int index = 0;
    while(m_nodeList[index]->y())
    {
        index++;
        continue;
    }
    m_nodeList.insert(index, m_nodeList.takeAt(m_nodeList.indexOf(_item)));
    updateNodeOrder();
}

#include <iostream>
void NodeTreeModel::updateNodeOrder(
        )
{
//    std::cerr<< "Order:\n";
//    foreach (NodeTreeItem* item, m_nodeList)
//    {
//        std::cerr << item->m_number << "\n";
//    }
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

