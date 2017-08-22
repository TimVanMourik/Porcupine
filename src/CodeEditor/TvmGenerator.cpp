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

#include <QJsonObject>
#include <QJsonArray>

#include "TvmGenerator.hpp"

const QString TvmGenerator::s_thisLanguage = QString("TvM");

TvmGenerator::TvmGenerator() :
    CodeGenerator(),
    m_configurationVariable("cfg")
{
}

QString TvmGenerator::generateCode(
        const QList<NodeTreeItem*>& _nodeList,
        const QVector<const Link*>& _linkList
        )
{
    Q_UNUSED(_linkList);
    QString code;
    foreach(const NodeTreeItem* item, _nodeList)
    {
        code += itemToCode(item);
    }
    return code;
}

QString TvmGenerator::itemToCode(
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    QJsonObject json = _item->getJson();
    Argument title(json["title"].toObject());
    if(title.getArgument(s_thisLanguage)["name"].isEmpty()) return QString("");
    code += QString("%% %1\n").arg(title.getComment(s_thisLanguage));
    code += QString("%1 = [];\n").arg(m_configurationVariable);
    //add input
    foreach (QJsonValue portObject, json["ports"].toArray())
    {
        Argument argument = Argument(portObject.toObject());
        code += argumentToCode(argument, _item);
    }
    //add function
    code += QString("%1(%2);\n\n").arg(title.getArgument(s_thisLanguage)["name"], m_configurationVariable);
    return code;
}

QString TvmGenerator::argumentToCode(
        const Argument& _argument,
        const NodeTreeItem* _item
        ) const
{
    QString code("");
    QString fileName = _item->getParameterName(_argument.m_argumentName);
    if(!_argument.getArgument(s_thisLanguage)["name"].isEmpty() && !fileName.isEmpty())
    {
        code += QString("%1.%2 = %3;").arg(m_configurationVariable, _argument.getArgument(s_thisLanguage)["name"], fileName);
        if(!_argument.getComment(s_thisLanguage).isEmpty())
        {
            code += "\t% ";
            code += _argument.getComment(s_thisLanguage);
        }
        code += "\n";
    }
    return code;
}

TvmGenerator::~TvmGenerator()
{
}

