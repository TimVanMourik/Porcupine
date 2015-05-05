#ifndef PORTPAIR_H
#define PORTPAIR_H

#include <QGraphicsTextItem>

#include "Argument.hpp"
#include "DataType.hpp"

class Node;
class Port;
class QDomElement;

class PortPair : public QGraphicsTextItem
{
public:
    //
    enum
    {
        Type = QGraphicsItem::UserType + 4
    };
    //
    PortPair(
            QGraphicsItem* _parent = 0
            );
    void createInputPort(
            );
    //
    void createOutputPort(
            );
    //
//    void createPorts(
//            );
    //
    Port* getInputPort(
            ) const;
    //
    Port* getOutputPort(
            ) const;
    //
    void setArgument(
            const Argument* _argument
            );
    //
    const QString& getName(
            ) const;
    //
    const QVector<const DataType*>& getType(
            ) const;
    //
    void saveToXml(
            QDomElement& _xmlElement
            );
    //
    void loadFromXml(
            QDomElement& _xmlNode,
            QMap<quint64, Port*>& o_portMap
            );
    //
    void hasFileName(
            bool _bool
            );
    //
    ~PortPair(
            );
private:
    //
    const Node* m_node;
    //
    QString m_name;
    //
    QVector<const DataType*> m_dataType;
    //
    Port* m_input;
    //
    Port* m_output;
    //
    bool m_hasFileName;
};

#endif // PORTPAIR_H
