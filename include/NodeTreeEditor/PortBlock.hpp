/*  Copyright (C) Tim van Mourik, 2017, DCCN
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

#ifndef PORTBLOCK_HPP
#define PORTBLOCK_HPP

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QVector>

#include "Node.hpp"

class QFormLayout;
class QLineEdit;
class PortPair;
class PortRow;

class PortBlock : public QWidget
{
    Q_OBJECT
public:
    explicit PortBlock(
            Node* _node,
            QWidget* _parent = 0
            );
    //
    void addPortBlock(
            const QVector<PortPair*>&
            );
    //
    void addPortRow(
            PortPair*
            );
    //
    void removePortRow(
            PortRow* _row
            );
    //
    void saveToJson(
            QJsonObject& o_json
            );
    //
    QString getParameterName(
            unsigned int _portId
            ) const;

public slots:
    //
    void addPort(
            );
private:
    //
    Node* m_node;
    //
    QFormLayout* m_layout;
    //
    QMap<unsigned int, PortRow*> m_parameterNames;
    //
    QVector<PortPair*> m_ports;
    //
//    QVector<PortRow*> m_portRows;
};

#endif // PORTBLOCK_HPP
