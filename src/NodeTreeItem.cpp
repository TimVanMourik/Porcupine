#include <QPushButton>

#include "DataType.hpp"
#include "Node.hpp"
#include "NodeTreeItem.hpp"
#include "PortPair.hpp"

NodeTreeItem::NodeTreeItem(
        const Node* _node
        ) :
//    QVBoxLayout(_node->getName()),
    QVBoxLayout(),
    m_node(_node)
{
    QPushButton* button = new QPushButton();
    button->setText(_node->getName());

    this->addWidget(button);
//    setEditable(false);
//    foreach(PortPair* pair, _node->getPorts())
//    {
//        QList<QStandardItem*> ports;

//        QStandardItem* nameItem = new QStandardItem(pair->getName());
//        nameItem->setEditable(false);
//        ports.append(nameItem);

//        QStandardItem* fileItem = new QStandardItem("<file name>");
//        fileItem->setEditable(true);
//        ports.append(fileItem);
//        m_ports[fileItem] = pair;

//        QStandardItem* dataItem = new QStandardItem(pair->getType()[0]->getName());
//        dataItem->setEditable(false);
//        ports.append(dataItem);

//        appendRow(ports);
//    }
}

void NodeTreeItem::setHasFilName(
        QStandardItem* _item,
        bool _hasFileName
        )
{
//    PortPair* port = m_ports[_item];
//    if(port)
//    {
//        if(_hasFileName)
//        {
//            port->setFileName(_hasFileName, _item->text(), true);
//        }
//        else
//        {
//            port->setFileName(_hasFileName, "", true);
//        }
//    }
}

bool NodeTreeItem::hasNode(
        const Node* _node
        )
{
//    if(m_node == _node)
//    {
//        return true;
//    }
//    else
//    {
        return false;
//    }
}

NodeTreeItem::~NodeTreeItem(
        )
{

}

