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
    m_portBlock(new QWidget(this)),
    m_node(_node)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    QWidget* widget1 = new QWidget(this);
    QHBoxLayout* layout1 = new QHBoxLayout(widget1);
    layout1->setSpacing(0);
    widget1->setLayout(layout1);
    m_portBlock->setParent(widget1);

    QLabel* nameTag = new QLabel();
    layout1->addWidget(nameTag);
    nameTag->setText(_node->getName());

    QPushButton* visibilityButton = new QPushButton();
    layout1->addWidget(visibilityButton);
    visibilityButton->setText("\\/");
    visibilityButton->setCheckable(true);

    mainLayout->addWidget(widget1);

    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, palette.window().color().darker(110));
    setAutoFillBackground(true);
    setPalette(palette);
    show();

//    QWidget* widget2 = new QWidget(this);
    QVBoxLayout* layout2 = new QVBoxLayout(m_portBlock);
    layout2->setSpacing(0);
    m_portBlock->setLayout(layout2);
    m_portBlock->setVisible(false);

    foreach(PortPair* pair, _node->getPorts())
    {
        QWidget* widget3 = new QWidget(m_portBlock);
        QHBoxLayout* layout3 = new QHBoxLayout();
        layout3->setSpacing(0);
        layout3->setContentsMargins(0, 0, 0, 0);
//        std::cerr << "Widget 3: top = " << widget3->contentsMargins().top() << ", bottom = " << widget3->contentsMargins().bottom() << "\n";
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
        m_ports[widget3] = pair;
    }
    mainLayout->addWidget(m_portBlock);

    connect(visibilityButton, SIGNAL(toggled(bool)), m_portBlock, SLOT(setVisible(bool)));
}

void NodeTreeItem::paintEvent(
        QPaintEvent* _event
        )
{
    Q_UNUSED(_event);
    foreach(QWidget* port, m_ports.keys())
    {
//        std::cerr << "Port: x = " << port->geometry().x() << ", y = " << port->geometry().y() << "\n";
//        std::cerr << "Port: top = " << ((QWidget*) port->parent())->contentsMargins().top() << ", bottom = " << ((QWidget*) port->parent())->contentsMargins().bottom() << "\n";
    }
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

void NodeTreeItem::setPortsVisible(
        bool _visibility
        )
{

}

NodeTreeItem::~NodeTreeItem(
        )
{
    foreach(QWidget* port, m_ports.keys())
    {
        ///@todo delete its children first
        delete port;
    }
}

