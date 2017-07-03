/*  Copyright (C) Tim van Mourik, 2014-2016
    Copyright (C) Tim van Mourik, 2017, DCCN
    All rights reserved

 This file is part of the Porcupine pipeline tool, see
 https://github.com/TimVanMourik/Porcupine for the documentation and
 details.

    This toolbox is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the fmri analysis toolbox. If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef PORTPAIR_H
#define PORTPAIR_H

#include <QGraphicsTextItem>
#include "Argument.hpp"

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
            bool _visible
            );
    //
    void createOutputPort(
            bool _visible
            );
    //
    void setArgument(
            const Argument& _argument
            );
    //
    const QString& getName(
            ) const;
    //
    const Argument& getArgument(
            ) const;
    //
    Port* getInputPort(
            ) const;
    //
    Port* getOutputPort(
            ) const;
    //
//    const QVector<const DataType*>& getType(
//            ) const;
    /// @brief returns if the port has ancestors
    bool hasAncestorPorts(
            );
    /// @brief returns the ancestors that are input-output connected via Links. Ancestry does not go via the parent Node.
    QVector<PortPair*> getAncestorPorts(
            );
    /// @brief returns if the port has descendants
    bool hasDescendantPorts(
            );
    /// @brief returns the descendants that are input-output connected via Links. Descendance does not go via the parent Node.
    QVector<PortPair*> getDescendantPorts(
            );
    //
//    QVector<const Node*> getAncestorNodes(
//            ) const;
    //
    QVector<const Node*> getDescendantNodes(
            ) const;
    //
    bool hasNodeAncestor(
            const Node* _node
            ) const;
    //
    void repositionPorts(
            qreal _width,
            qreal _height
            );
    //
    const QString& getFileName(
                ) const;
    //
    bool isIterator(
                ) const;
    //
    ~PortPair(
            );
signals:
    //
    void changeFileName(
            const QString& _fileName
            );
    //
    void isConnected(
            bool _connected
            );
public slots:
    /// @brief
    /// @param _cascadeUp indicates if the file name should be passed up the hierarchy or only down
    void fileNameChanged(
            const QString& _fileName = "",
            bool _cascadeUp = true
            );
    //
    void setVisibility(
            bool _visibility
            );
    //
    void setAsIterator(
            bool _iterator
            );
    //
    const QJsonObject& toJson(
            );
    //
    void removePort(
            );
private:
    //
    Node* m_node;
    //
    Argument m_argument;
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
