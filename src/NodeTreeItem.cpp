#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

#include "DataType.hpp"
#include "Node.hpp"
#include "NodeTreeItem.hpp"
#include "PortPair.hpp"

#include <iostream>
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

    QLabel* button1 = new QLabel();
    layout1->addWidget(button1);
    button1->setText(_node->getName());

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
        QWidget* widget3 = new QWidget(widget2);
        QHBoxLayout* layout3 = new QHBoxLayout();
//        std::cerr << "Layout2: x = " << layout2->geometry().x() << ", y = " << layout3->geometry().y() << "\n";
//        std::cerr << "Layout3: x = " << layout3->geometry().x() << ", y = " << layout3->geometry().y() << "\n";
//        layout3->setGeometry(QRect(0, 0, 100, 10));
        widget3->setLayout(layout3);

        QLabel* portName = new QLabel(pair->getName());
        layout3->addWidget(portName);

        QLabel* fileName = new QLabel("<file name>");
        layout3->addWidget(fileName);

        QComboBox* dataType = new QComboBox();
        foreach(const DataType* type, pair->getType())
        {
            dataType->addItem(type->getName());
        }
        layout3->addWidget(dataType);
        layout2->addWidget(widget3);
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

