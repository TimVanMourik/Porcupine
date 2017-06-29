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

#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVector>

class DataType;

class Argument
{
public:
    //
    Argument(
            const QJsonObject& _json = QJsonObject()
            );
    //
    bool isInput(
            ) const;
    //
    bool isOutput(
            ) const;
    //
    bool isVisible(
            ) const;
    //
    bool isEditable(
            ) const;
    //
    bool isIterator(
            ) const;
    //
    void setName(
            const QString& _name
            );
    //
    void setDefault(
            const QString& _name
            );
    //
    void setVisible(
            bool _visible
            );
    //
    void setEditable(
            bool _editable
            );
    //
    void setIterator(
            bool _iterator
            );
    //
    const QString& getName(
            ) const;
    //
    const QString& getDefault(
            ) const;
    //
    QString getArgument(
            const QString& _language
            ) const;
    //
    const QJsonObject& getJson(
            ) const;
    //
    QString getComment(
            const QString& _language
            ) const;
    //
    unsigned int numberOfCodeRules(
            );
    //
    void addCode(
            const QString& _language,
            const QString& _argument,
            const QString& _comment = QString("")
            );

private:
    //
    QJsonObject m_json;
    //
    bool m_isInput;
    //
    bool m_isOutput;
    //
    bool m_isVisible;
    //
    bool m_isEditable;
    //
    bool m_isIterator;
    //
    QString m_argumentName;
    //
    QString m_defaultValue;
    //
    struct Code
    {
        QString argument;
        QString comment;
    };
    //
    QMap<QString, Code> m_code;
};

#endif // ARGUMENT_HPP
