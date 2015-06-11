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
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(2, 2, 2, 2);

    setLayout(mainLayout);
    QWidget* widget1 = new QWidget(this);
    QHBoxLayout* layout1 = new QHBoxLayout(widget1);
    layout1->setSpacing(0);
    layout1->setContentsMargins(2, 0, 2, 0);
    widget1->setLayout(layout1);
    m_portBlock->setParent(widget1);

    QLabel* nameTag = new QLabel();
    nameTag->setText(_node->getName());
    layout1->addWidget(nameTag);

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

    QVBoxLayout* layout2 = new QVBoxLayout(m_portBlock);
    layout2->setSpacing(0);
    layout2->setContentsMargins(4, 3, 3, 3);
    m_portBlock->setLayout(layout2);
    m_portBlock->setVisible(false);

    foreach(PortPair* pair, _node->getPorts())
    {
        QWidget* widget3 = new QWidget(m_portBlock);
        QHBoxLayout* layout3 = new QHBoxLayout();
        layout3->setSpacing(0);
        layout3->setContentsMargins(2, 0, 2, 0);
        widget3->setLayout(layout3);

        QLabel* portName = new QLabel(pair->getName());
        layout3->addWidget(portName);

        QLabel* fileName = new QLabel("<file name>");
        fileName->setTextInteractionFlags(Qt::TextEditorInteraction);
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

//void NodeTreeItem::paintEvent(
//        QPaintEvent* _event
//        )
//{
//    Q_UNUSED(_event);
//    foreach(QWidget* port, m_ports.keys())
//    {
//    }
//}

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

