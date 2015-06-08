#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>

#include "DataType.hpp"
#include "Node.hpp"
#include "NodeTreeItem.hpp"
#include "PortPair.hpp"

NodeTreeItem::NodeTreeItem(
        const Node* _node
        ) :
    QWidget(),
    m_layout(new QVBoxLayout(this)),
    m_node(_node)
{
    setLayout(m_layout);
    QWidget* widget1 = new QWidget(this);
    QHBoxLayout* layout1 = new QHBoxLayout(widget1);
    widget1->setLayout(layout1);

    QPushButton* button1 = new QPushButton();
    layout1->addWidget(button1);
    button1->setText(_node->getName());
    button1->setDisabled(true);

    QPushButton* button2 = new QPushButton();
    layout1->addWidget(button2);
    button2->setText("\\/");
    button2->setCheckable(false);

    m_layout->addWidget(widget1);

    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, palette.window().color().darker(110));
    setAutoFillBackground(true);
    setPalette(palette);
    show();

    QWidget* widget2 = new QWidget(this);
    QVBoxLayout* layout2 = new QVBoxLayout(widget2);
    widget2->setLayout(layout2);

    foreach(PortPair* pair, _node->getPorts())
    {
        QPushButton* button = new QPushButton();
        layout2->addWidget(button);
        button->setText(pair->getName());
//        QList<QStandardItem*> ports;

//        QStandardItem* nameItem = new QStandardItem(pair->getName());
//        nameItem->setEditable(false);

//        QStandardItem* fileItem = new QStandardItem("<file name>");
//        fileItem->setEditable(true);
//        m_ports[fileItem] = pair;

        QComboBox* comboBox = new QComboBox();
        layout2->addWidget(comboBox);
        foreach(const DataType* type, pair->getType())
        {
            comboBox->addItem(type->getName());
        }


//        appendRow(ports);
    }
    m_layout->addWidget(widget2);
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

