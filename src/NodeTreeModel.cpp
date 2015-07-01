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
    NodeTreeItem* item = new NodeTreeItem(_node, this);
    m_layout->addWidget(item);
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

