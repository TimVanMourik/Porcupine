#ifndef NODEANTENNA_H
#define NODEANTENNA_H

#include <QObject>

class Node;

class NodeAntenna : public QObject
{
    Q_OBJECT
public:
    //
    NodeAntenna(
            );
    //
    void setNode(
            Node* _node
            );
    //
    void sendLabelChanged(
            const QString& _name
            );
    //
    void sendNodeSelected(
            bool _isSelected
            );
signals:
    //
    void nodeNameChanged(
        const QString& _name
        );
    //
    void nodeSelected(
            bool _isSelected
            );
public slots:
    //
    void catchLabelChanged(
            const QString& _name
            );
    //
    void catchSelected(
            bool _selected
            );

private:
    //
    Node* m_node;
};

#endif // NODEANTENNA_H
