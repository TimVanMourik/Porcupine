#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
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
    m_node(_node),
    m_portBlock(new QWidget(this))
{
    int minimumSize = 0;
    int spacing = 2;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(2, 2, 2, 2);

    setLayout(mainLayout);
    QWidget* headerWidget = new QWidget(this);
    QHBoxLayout* layout1 = new QHBoxLayout(headerWidget);
    layout1->setSpacing(0);
    layout1->setContentsMargins(2, 10, 20, 0);
    headerWidget->setLayout(layout1);
    m_portBlock->setParent(headerWidget);

    QLabel* nameTag = new QLabel();
    nameTag->setText(_node->getName());
    layout1->addWidget(nameTag);

    QPushButton* visibilityButton = new QPushButton();
    visibilityButton->setMaximumWidth(30);
    layout1->addWidget(visibilityButton);
    visibilityButton->setText("\\/");
    visibilityButton->setCheckable(true);

    mainLayout->addWidget(headerWidget);

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
        ///@todo this pointer isn't explicitly deleted yet
        QHBoxLayout* layout3 = new QHBoxLayout();
        ///@todo this pointer isn't explicitly deleted yet
        QWidget* portWidget = new QWidget(m_portBlock);
        portWidget->setLayout(layout3);
        layout3->setSpacing(spacing);
        layout3->setContentsMargins(2, 0, 2, 0);

        ///@todo this pointer isn't explicitly deleted yet
        QLabel* portName = new QLabel(pair->getName());
        layout3->addWidget(portName);

        ///@todo this pointer isn't explicitly deleted yet
        QLineEdit* fileName = new QLineEdit();
        QFont font = QFont();
        font.setItalic(true);
//        fileName->setMaximumHeight(fileName->font().pointSize() + 4);
        fileName->setFont(font);

        fileName->setText("<file name>");
        fileName->font().pointSize();
        QPalette palette = fileName->palette();
        palette.setColor(fileName->backgroundRole(), Qt::white);

        fileName->setAutoFillBackground(true);
        fileName->setPalette(palette);
        layout3->addWidget(fileName);

        ///@todo this pointer isn't explicitly deleted yet
        QComboBox* dataType = new QComboBox();
        foreach(const DataType* type, pair->getType())
        {
            dataType->addItem(type->getName());
        }
        layout3->addWidget(dataType);
        minimumSize += fileName->font().pointSize() + spacing;

//        m_portBlock->setMinimumHeight(3 * (fileName->font().pointSize() + spacing) * m_ports.size());
//        m_portBlock->setMaximumHeight(3 * (fileName->font().pointSize() + spacing) * m_ports.size());
        m_ports[portWidget] = pair;

        layout2->addWidget(portWidget);

        connect(fileName, SIGNAL(textEdited(QString)), pair, SLOT(fileNameChanged(QString)));
        connect(pair, SIGNAL(changeFileName(QString)), fileName, SLOT(setText(QString)));
    }
//    setMinimumHeight(m_portBlock->minimumHeight() + 30);
//    setMaximumHeight(m_portBlock->minimumHeight() + 30);
    mainLayout->addWidget(m_portBlock);

    connect(visibilityButton, SIGNAL(toggled(bool)), m_portBlock, SLOT(setVisible(bool)));
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

//void NodeTreeItem::setPortsVisible(
//        bool _visibility
//        )
//{

//}

NodeTreeItem::~NodeTreeItem(
        )
{
    foreach(QWidget* port, m_ports.keys())
    {
        ///@todo delete its children first
        delete port;
    }
}

