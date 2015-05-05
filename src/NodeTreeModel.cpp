#include "FileNameItem.hpp"
#include "NodeTreeModel.hpp"
#include "PortPair.hpp"

NodeTreeModel::NodeTreeModel(
        ) :
    QStandardItemModel()
{
    setHorizontalHeaderItem(0, new QStandardItem( "Node" ));
    setHorizontalHeaderItem(1, new QStandardItem( "File name" ));
    setHorizontalHeaderItem(2, new QStandardItem( "Data type" ));

    connect(this, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(fileNameFieldChanged(QStandardItem*)));
}

void NodeTreeModel::fileNameFieldChanged(
        QStandardItem* _item
        )
{
    if(_item->type() == FileNameItem::Type)
    {
        FileNameItem* field = (FileNameItem*) _item;
        if(field->text().compare("<file name>") == 0 || field->text().compare("") == 0)
        {
            field->setText("<file name>");
            field->hasFileName(false);
        }
        else
        {
            field->hasFileName(true);
        }
    }
}

void NodeTreeModel::addNode(
        const Node* _node
        )
{
    QStandardItem* item = new QStandardItem(_node->getName());
    item->setEditable(false);
    foreach(PortPair* pair, _node->getPorts())
    {
        QList<QStandardItem*> ports;

        QStandardItem* nameItem = new QStandardItem(pair->getName());
        nameItem->setEditable(false);
        ports.append(nameItem);

        FileNameItem* fileItem = new FileNameItem("<file name>");
        fileItem->setEditable(true);
        fileItem->setPort(pair);
//        ports.append((QStandardItem*) fileItem);
        ports.append((FileNameItem*) fileItem);

        QStandardItem* dataItem = new QStandardItem(pair->getType()[0]->getName());
        dataItem->setEditable(false);
        ports.append(dataItem);

        item->appendRow(ports);
    }
    setItem(this->rowCount(), 0, item);
}


NodeTreeModel::~NodeTreeModel(
        )
{
//    delete all items;
}

