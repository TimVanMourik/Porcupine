#include <QApplication>
#include <QComboBox>
#include <QDomDocument>
#include <QDrag>
#include <QDropEvent>
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
    m_position(QPoint()),
    m_numberLabel(0),
    m_number(0)
{
    int minimumSize = 0;
    int spacing = 2;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QWidget* headerWidget = new QWidget();
    QWidget* portBlock = new QWidget();
    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(portBlock);
    QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
    QHBoxLayout* portBlockLayout = new QHBoxLayout(portBlock);

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
    m_numberLabel = new QLabel();
    QLabel* nameTag = new QLabel();
    QPushButton* visibilityButton = new QPushButton();
    headerLayout->addWidget(m_numberLabel);
    headerLayout->addWidget(nameTag);
    headerLayout->addWidget(visibilityButton);

    m_numberLabel->setText(QString::number(m_number));
    nameTag->setText(_node->getName());
    visibilityButton->setMaximumWidth(30);
    visibilityButton->setText("\\/");
    visibilityButton->setCheckable(true);

    // portBlockLayout
    portBlockLayout->setSpacing(0);
    portBlockLayout->setContentsMargins(4, 3, 3, 3);
    portBlock->setLayout(portBlockLayout);
    portBlock->setVisible(false);

    /// @todo Make two colums, one for the port name, one for the file name
    QWidget* left  = new QWidget();
    QWidget* right = new QWidget();
    portBlockLayout->addWidget(left);
    portBlockLayout->addWidget(right);
    QVBoxLayout* leftLayout = new QVBoxLayout(left);
    QVBoxLayout* rightLayout = new QVBoxLayout(right);
    leftLayout->setSpacing(spacing);
    leftLayout->setContentsMargins(2, 0, 2, 0);
    rightLayout->setSpacing(spacing);
    rightLayout->setContentsMargins(2, 0, 2, 0);
    foreach(PortPair* pair, _node->getPorts())
    {
        QLabel* portName = new QLabel(pair->getName());
        QLineEdit* fileName = new QLineEdit();
        leftLayout->addWidget(portName);
        rightLayout->addWidget(fileName);

        m_fileNames[pair->getName()] = fileName;
        QFont font = QFont();
        QString name = pair->getFileName();
        if(!name.isEmpty())
        {
            font.setItalic(false);
            fileName->setText(name);
        }
        else
        {
            font.setItalic(true);
            fileName->setText("<file name>");
        }
        fileName->setFont(font);
        fileName->font().pointSize();
        QPalette palette = fileName->palette();
        palette.setColor(fileName->backgroundRole(), Qt::white);

        fileName->setAutoFillBackground(true);
        fileName->setPalette(palette);
        minimumSize += fileName->font().pointSize() + spacing;

        connect(fileName, SIGNAL(textEdited(QString)), pair, SLOT(fileNameChanged(QString)));
        /// @todo set the SLOT such that it does not only handle the text but also the font
        connect(pair, SIGNAL(changeFileName(QString)), fileName, SLOT(setText(QString)));
    }
    connect(visibilityButton, SIGNAL(toggled(bool)), portBlock, SLOT(setVisible(bool)));
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
    raise();
//    setWindowOpacity(0.5);
    if(_event->button() == Qt::LeftButton)
    {
        m_position = _event->globalPos();
    }
}

void NodeTreeItem::mouseMoveEvent(
        QMouseEvent* _event
        )
{

    const QPoint delta = _event->globalPos() - m_position;
    move(x(), y() + delta.y());
    m_position = _event->globalPos();
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

NodeTreeItem::~NodeTreeItem(
        )
{
}

