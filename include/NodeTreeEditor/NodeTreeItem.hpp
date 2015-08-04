#ifndef NODETREEITEM_H
#define NODETREEITEM_H

#include <QGraphicsPathItem>
#include <QPoint>
#include <QStandardItem>
#include <QFrame>

class Node;
class NodeSetting;
class PortPair;
class QDomDocument;
class QDomElement;
class QLabel;
class QLineEdit;
class QVBoxLayout;

#include "Hider.hpp"

class NodeTreeItem : public QFrame
{
    Q_OBJECT
public:
    ///@todo make sure that the item doesn't flash before moving to the right position
    NodeTreeItem(
            const Node* _node,
            QWidget* _parent
            );
    //
    void setPort(
            PortPair* _port
            );
    //
    bool isAncestorOf(
            NodeTreeItem* _item
            );
    //
    void saveToXml(
            QDomElement& _xmlElement
            ) const;
    //
    const Node* getNode(
            ) const;
    //
    const NodeSetting* getNodeSetting(
            ) const;
    //
    QVector<const Node*> getDescendants(
            );
    //
    void setNumber(
            unsigned int _i
            );
    //
    QString getFileName(
            const QString& _portName
            ) const;
    //
    void mousePressEvent(
            QMouseEvent* _event
            );
    //
    void mouseMoveEvent(
            QMouseEvent* _event
            );
    //
    void mouseReleaseEvent(
            QMouseEvent* _event
            );
    //
    virtual ~NodeTreeItem(
            );
public slots:
    //
    void setSelected(
            bool _isSelected
            );
signals:
    void moved(
            NodeTreeItem* _item
            );
private:
    //
    const Node* m_node;
    //
    QMap<QWidget*, PortPair*> m_ports;
    //
    QMap<QString, QLineEdit*> m_fileNames;
    //
    QPoint m_startPosition;
    //
    QLabel* m_numberLabel;
    //
    unsigned int m_number;
};

#endif // NODETREEITEM_H
