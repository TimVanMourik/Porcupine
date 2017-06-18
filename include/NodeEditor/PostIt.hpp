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

#ifndef POSTIT_HPP
#define POSTIT_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file PostIt.hpp
/// @author Tim van Mourik
/// @date 13 June 2017
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QGraphicsPathItem>

class QLineEdit;
class QTextEdit;

class NodeEditor;

class PostIt : public QGraphicsPathItem
{
public:
    //
    enum
    {
        Type = QGraphicsItem::UserType + 5
    };

    //
    PostIt(
            NodeEditor* _editor
            );
    //
    void paint(
            QPainter* _painter,
            const QStyleOptionGraphicsItem* _option,
            QWidget* _widget
            );
    //
    int type(
            ) const;
    //
    void labelNameChanged(
            const QString& _name
            );
    //
    void saveToJson(
            QJsonObject& o_json
            );
    //
    void loadFromJson(
            const QJsonObject& _json
            );
    //
//    QVariant itemChange(
//            GraphicsItemChange _change,
//            const QVariant& _value
//            );
    //
    ~PostIt(
            );
private:
    //
    QLineEdit* m_nameLabel;
    //
    QTextEdit* m_text;
    //
    static qreal s_horizontalMargin;
    //
    static qreal s_verticalMargin;
    //
    static qreal s_textSpacing;
};

#endif // POSTIT_HPP
