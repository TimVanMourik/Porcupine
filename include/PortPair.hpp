#ifndef PORTPAIR_H
#define PORTPAIR_H

#include <QGraphicsTextItem>

class Argument;
class DataType;
class Node;
class Port;
class QDomElement;

class PortPair : public QGraphicsTextItem
{
    Q_OBJECT
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
    void setArgument(
            const Argument* _argument
            );
    //
    const QString& getName(
            ) const;
    //
    Port* getInputPort(
            ) const;
    //
    Port* getOutputPort(
            ) const;
    //
    const QVector<const DataType*>& getType(
            ) const;
    /// @brief returns if the port has ancestors
    bool hasAncestors(
            );
    /// @brief returns the ancestors that are input-output connected via Links. Ancestry does not go via the parent Node.
    QVector<PortPair*> getAncestors(
            );
    /// @brief returns if the port has descendants
    bool hasDescendants(
            );
    /// @brief returns the descendants that are input-output connected via Links. Descendance does not go via the parent Node.
    QVector<PortPair*> getDescendants(
            );
    //
    bool hasAncestor(
            const Node* _node
            ) const;
    //
    void repositionPorts(
            qreal _width,
            qreal _height
            );
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
    const QString& getFileName(
                );
    //
    ~PortPair(
            );
signals:
    //
    void changeFileName(
            const QString& _fileName
            );
public slots:
    /// @brief
    /// @param _cascadeUp indicates if the file name should be passed up the hierarchy or only down
    void fileNameChanged(
            const QString& _fileName = "",
            bool _cascadeUp = true
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
    QString m_fileName;
    //
    bool m_hasFileName;
};

#endif // PORTPAIR_H
