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

#include <QMap>
#include <QString>
#include <QVector>

class DataType;

class Argument
{
public:
    enum FieldType
    {
        NONE    = 0,
        INPUT   = 1,
        OUTPUT  = 2,
        INOUT   = 3,
        HIDDEN  = 4, //hidden in the NodeEditor
        SECRET  = 5  //also hidden in the NodeTreeEditor
    };
    //
    Argument(
            const QString& _argumentName = QString(),
            FieldType _type = NONE,
            QString _defaultValue = QString("")
            );
    //
    bool isVisible(
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
            bool _editable
            );
    //
    void setType(
            const FieldType& _type
            );
    //
    const QString& getName(
            ) const;
    //
    const QString& getDefault(
            ) const;
    //
    const FieldType& getType(
            ) const;
    //
    QString getArgument(
            const QString& _language
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
    //
//    const QVector<const DataType*>& getType(
//            ) const;

private:
    //
    FieldType m_portType;
    //
    QString m_argumentName;
    //
    QString m_defaultValue;
    //
    bool m_isVisible;
    //
    struct Code
    {
        QString argument;
        QString comment;
    };
    //
    QMap<QString, Code> m_code;
    //
//    const QVector<const DataType*> m_type;

};

#endif // ARGUMENT_HPP
