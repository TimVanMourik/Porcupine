#include "NodeTreeItem.hpp"
#include "NodeTreeModel.hpp"
#include "PortPair.hpp"

NodeTreeModel::NodeTreeModel(
        ) :
    QStandardItemModel()
{
    setHorizontalHeaderItem(0, new QStandardItem( "Node" ));
    setHorizontalHeaderItem(1, new QStandardItem( "File name" ));
    setHorizontalHeaderItem(2, new QStandardItem( "Data type" ));

    //The only editable item is the file name item, but it's also called when the other QStandardItems are constructed
    connect(this, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(fileNameFieldChanged(QStandardItem*)));
}

void NodeTreeModel::fileNameFieldChanged(
        QStandardItem* _item
        )
{
    if(_item->parent())
    {
        NodeTreeItem* nodeItem = (NodeTreeItem*) _item->parent();

        if(_item->text().compare("<file name>") == 0 || _item->text().compare("") == 0)
        {
            _item->setText("<file name>");
            nodeItem->setHasFilName((QStandardItem*) _item, false);
//            _item->hasFileName(false);
        }
        else
        {
            nodeItem->setHasFilName((QStandardItem*) _item, true);
//            _item->hasFileName(true);
        }
    }
}

void NodeTreeModel::addNode(
        const Node* _node
        )
{
//    m_nodes.append(_node);
    NodeTreeItem* item = new NodeTreeItem(_node);
    setItem(this->rowCount(), 0, item);
}

void NodeTreeModel::removeNode(
        const Node* _node
        )
{
    for(int i = 0; i < rowCount(); ++i)
    {
        if(((NodeTreeItem*) item(i))->hasNode(_node))
        {
            removeRow(i);
            break;
        }
    }
}


NodeTreeModel::~NodeTreeModel(
        )
{
//    delete all items;
}

