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

#ifndef PORTROW_HPP
#define PORTROW_HPP

#include <QObject>
#include <QFormLayout>
#include <QMap>
#include <QVector>
#include <QWidget>

class QCheckBox;
class QLineEdit;
class PortBlock;
class PortPair;

class PortRow : public QWidget
{
    Q_OBJECT
public:
    explicit PortRow(
            PortPair* _port,
            PortBlock* _parent = 0
            );
    //
    void addPortRow(
            const QVector<PortPair*>&
            );
    //
    void saveToJson(
            QJsonObject& o_json
            ) const;
    //
    QString getParameterName(
            ) const;
    //
    void initialiseStyleSheets(
            );
    //
    ~PortRow(
            );
public slots:
    //
    void removePort(
            );
    //
    void iteratePort(
            bool _iterator
            );
    //
    void showPort(
            bool _visible
            );
private:
    //
    PortBlock* m_parent;
    //
    PortPair* m_port;
    //
    QLineEdit* m_parameterName;
    //
    QCheckBox* m_showCheckbox;
    //
    QCheckBox* m_iterateCheckbox;
    //
    QCheckBox* m_deleteButton;
};

#endif // PORTROW_HPP
