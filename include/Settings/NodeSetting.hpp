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

#ifndef NODESETTING_H
#define NODESETTING_H

//----------------------------------------------------------------------------------------------------------------------
/// @file NodeSetting.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QColor>
#include <QJsonObject>
#include <QStringList>

#include "Argument.hpp"

class NodeSetting
{
public:
    //
    NodeSetting(
            const Argument& _title,
            const QJsonObject& _json
            );
    //
    void setColour(
            const QColor& _colour
              );
    //
    const Argument& getTitle(
            ) const;
    //
    const QJsonObject& getJson(
            ) const;
    //
    void setCategory(
            const QStringList& _category
            );
    //
    const QStringList& getCategory(
            ) const;
    //
    ~NodeSetting(
            );
private:
    //
    Argument m_title;
    //
    QJsonObject m_json;
    //
    QStringList m_category;
    //
    QColor m_nodeColour;
};

#endif // NODESETTING_H
