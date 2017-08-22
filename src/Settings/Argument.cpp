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

#include <QDebug>
#include <QJsonArray>

#include "Argument.hpp"

Argument::Argument(
        const QJsonObject& _json
        ) :
    m_json(_json),
    m_isInput     (_json["input"   ].toBool()),
    m_isOutput    (_json["output"  ].toBool()),
    m_isVisible   (_json["visible" ].toBool()),
    m_isEditable  (_json["editable"].toBool()),
    m_isIterator  (_json["iterator"].toBool()),
    m_argumentName(_json["name"    ].toString()),
    m_defaultValue(_json["value"   ].toString()),
    m_webUrl      (_json["web_url" ].toString())
{
    foreach (QJsonValue code, _json["code"].toArray())
    {
        QJsonObject codeJson = code.toObject();
        QMap<QString, QString> argumentList;
        QJsonObject arguments = codeJson["argument"].toObject();
        foreach (QString key, arguments.keys())
        {
            argumentList[key] = arguments[key].toString();
        }
        addCode(codeJson["language"].toString(),
                argumentList,
                codeJson["comment" ].toString());
    }
}

QMap<QString, QString> Argument::getArgument(
        const QString& _language
        ) const
{
    if(m_code.contains(_language))
    {
        return m_code[_language].argument;
    }
    else
    {
        return QMap<QString, QString>();
    }
}

void Argument::updateJson(
        )
{
    QJsonArray codeArray;
    for(QMap<QString, Code>::iterator it = m_code.begin(); it != m_code.end(); ++it)
    {
        QJsonObject code;
        code["language"] = it.key();
        code["argument"] = map2Json(it.value().argument);
        code["comment" ] = it.value().comment;
        codeArray << code;
    }
    m_json["code"    ] = codeArray;
    m_json["input"   ] = m_isInput;
    m_json["output"  ] = m_isOutput;
    m_json["visible" ] = m_isVisible;
    m_json["editable"] = m_isEditable;
    m_json["iterator"] = m_isIterator;
    m_json["name"    ] = m_argumentName;
    m_json["value"   ] = m_defaultValue;
}

QJsonObject Argument::map2Json(
        const QMap<QString, QString>& _argument
        )
{
    QJsonObject object;
    foreach (QString key, _argument.keys())
    {
        object[key] = _argument[key];
    }
    return object;
}

const QJsonObject& Argument::toJson(
        ) const
{
    return m_json;
}

QList<QString> Argument::getLanguages(
        )
{
    return m_code.keys();
}

QString Argument::getComment(
        const QString& _language
        ) const
{
    if(m_code.contains(_language))
    {
        return m_code[_language].comment;
    }
    else
    {
        return QString();
    }
}

void Argument::addCode(
        const QString& _language,
        const QMap<QString, QString>& _argument,
        const QString& _comment
        )
{
    m_code[_language] = Code();
    m_code[_language].argument = _argument;
    m_code[_language].comment  = _comment;
}
