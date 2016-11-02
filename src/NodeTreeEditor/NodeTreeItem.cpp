#include <QApplication>
#include <QComboBox>
#include <QDomDocument>
#include <QDrag>
#include <QDropEvent>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMimeData>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

#include "DataType.hpp"
#include "Node.hpp"
#include "NodeTreeItem.hpp"
#include "PortPair.hpp"

NodeTreeItem::NodeTreeItem(
        const Node* _node,
        QWidget* _parent
        ) :
    QFrame(_parent),
    m_node(_node),
    m_startPosition(QPoint()),
    m_numberLabel(0),
    m_number(0),
    m_isSelected(false)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QWidget* headerBlock = new QWidget();
    QWidget* portBlock = new QWidget();
    mainLayout->addWidget(headerBlock);
    mainLayout->addWidget(portBlock);
    QHBoxLayout* headerLayout = new QHBoxLayout(headerBlock);
    QFormLayout* portBlockLayout = new QFormLayout(portBlock);

    setFrameShadow(QFrame::Raised);
    setFrameStyle(QFrame::StyledPanel);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, palette.window().color().darker(110));
    setAutoFillBackground(true);
    setPalette(palette);
    show();

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(2, 2, 2, 2);
    headerLayout->setSpacing(0);
    headerLayout->setContentsMargins(10, 10, 20, 0);

    // headerLayout
    m_numberLabel = new QLabel(QString::number(m_number));
    QLabel* nameTag = new QLabel(_node->getName());
    connect(&m_node->getAntenna(), SIGNAL(nodeNameChanged(QString)), nameTag, SLOT(setText(QString)));

    QPushButton* visibilityButton = new QPushButton();
    visibilityButton->setMaximumWidth(30);
    visibilityButton->setText("\\/");
    visibilityButton->setCheckable(true);

    headerLayout->addWidget(m_numberLabel);
    headerLayout->addWidget(nameTag);
    headerLayout->addWidget(visibilityButton);

    // portBlockLayout
    portBlockLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
    portBlockLayout->setVerticalSpacing(3);
    portBlockLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    portBlockLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    portBlockLayout->setLabelAlignment(Qt::AlignHCenter);
    portBlock->setVisible(false);

    foreach(PortPair* pair, _node->getPorts())
    {
        QLineEdit* fileName = new QLineEdit();
        fileName->setPlaceholderText("<value>");

        m_fileNames[pair->getName()] = fileName;
        QString name = pair->getFileName();
        if(!name.isEmpty())
        {
            fileName->setText(name);
        }
        if(pair->isSecret())
        {
            continue;
        }
        portBlockLayout->addRow(pair->getName(), fileName);

        connect(fileName, SIGNAL(textEdited(QString)), pair, SLOT(fileNameChanged(QString)));
        /// @todo set the SLOT such that it does not only handle the text but also the font
        connect(pair, SIGNAL(changeFileName(QString)), fileName, SLOT(setText(QString)));
    }
    connect(visibilityButton, SIGNAL(toggled(bool)), portBlock, SLOT(setVisible(bool)));
    connect(&m_node->getAntenna(), SIGNAL(nodeSelected(bool)), this, SLOT(setSelected(bool)));
}

QString NodeTreeItem::getFileName(
        const QString& _portName
        ) const
{
    if(m_fileNames[_portName])
    {
        return m_fileNames[_portName]->text();
    }
    else
    {
        return QString("");
    }
}

bool NodeTreeItem::isAncestorOf(
        NodeTreeItem* _item
        )
{
    return _item->getNode()->hasAncestor(m_node);
}

const Node* NodeTreeItem::getNode(
        ) const
{
    return m_node;
}

const NodeSetting* NodeTreeItem::getNodeSetting(
        ) const
{
    return m_node->getSetting();
}

QVector<const Node*> NodeTreeItem::getDescendants(
        )
{
    return m_node->getDescendants();
}

void NodeTreeItem::saveToXml(
        QDomElement& _xmlElement
        ) const
{
    QDomDocument xml;
    QDomElement node = xml.createElement("node");
    node.setAttribute("name", m_node->getName());
    node.setAttribute("type", m_node->getType());
    QDomElement position = xml.createElement("position");
    position.setAttribute("x", QString::number(m_node->pos().x()));
    position.setAttribute("y", QString::number(m_node->pos().y()));
    node.appendChild(position);

    QDomElement ports = xml.createElement("pairs");
    foreach(const PortPair* pair, m_node->getPorts())
    {
        pair->saveToXml(ports);
    }
    node.appendChild(ports);
    _xmlElement.appendChild(node);
}

void NodeTreeItem::mousePressEvent(
        QMouseEvent* _event
        )
{
//    if(m_isSelected)
//    {
//       setSelected(false);
//    }
//    else
//    {
//        setSelected(true);
//    }
    raise();
//    setWindowOpacity(0.5);
    if(_event->button() == Qt::LeftButton)
    {
        m_startPosition = _event->globalPos();
    }
}

void NodeTreeItem::mouseMoveEvent(
        QMouseEvent* _event
        )
{
    const QPoint delta = _event->globalPos() - m_startPosition;
    move(x(), y() + delta.y());
    m_startPosition = _event->globalPos();
}

void NodeTreeItem::mouseReleaseEvent(
        QMouseEvent* _event
        )
{
    Q_UNUSED(_event);
//    setWindowOpacity(1);
    emit moved(this);
}

void NodeTreeItem::setNumber(
        unsigned int _i
        )
{
    m_number = _i;
    m_numberLabel->setText(QString::number(m_number));
}


void NodeTreeItem::setSelected(
        bool _isSelected
        )
{
    m_isSelected = _isSelected;
    if(_isSelected)
    {
        setObjectName("myObject");
        setStyleSheet("#myObject {border: 2px solid black;}");
    }
    else
    {
        setStyleSheet("");
    }
}

NodeTreeItem::~NodeTreeItem(
        )
{
}

