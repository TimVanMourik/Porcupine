#include "Node.hpp"
#include "NodeAntenna.hpp"

NodeAntenna::NodeAntenna(
        ) :
    QObject(0)
{

}

void NodeAntenna::setNode(
        Node* _node
        )
{
    m_node = _node;
}

void NodeAntenna::catchLabelChanged(
        const QString& _name
        )
{
    m_node->labelNameChanged(_name);
}

void NodeAntenna::sendLabelChanged(
        const QString& _name
        )
{
    emit nodeNameChanged(_name);
}
