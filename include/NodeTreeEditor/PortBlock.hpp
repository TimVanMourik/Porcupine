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
#include <QFormLayout>
#include <QMap>
#include <QVector>

class QLineEdit;
class PortPair;
class PortRow;

class PortBlock : public QFormLayout
{
    Q_OBJECT
public:
    explicit PortBlock(
            QWidget* _parent = 0
            );
    //
    void addPortBlock(
            const QVector<PortPair*>&
            );
    //
//    void addPortRow(
//            const PortPair*
//            );
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
            const QString& _portName
            ) const;
    //

public slots:
private:
    //
    QMap<QString, QLineEdit*> m_parameterNames;
    //
    QVector<PortPair*> m_ports;
    //
    QVector<PortRow*> m_portRows;
};

#endif // PORTBLOCK_HPP
