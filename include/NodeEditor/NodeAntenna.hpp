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

#ifndef NODEANTENNA_H
#define NODEANTENNA_H

#include <QObject>

class Node;

class NodeAntenna : public QObject
{
    Q_OBJECT
public:
    //
    NodeAntenna(
            );
    //
    void setNode(
            Node* _node
            );
    //
    void sendLabelChanged(
            const QString& _name
            );
    //
    void sendNodeSelected(
            bool _isSelected
            );
signals:
    //
    void nodeNameChanged(
        const QString& _name
        );
    //
    void nodeSelected(
            bool _isSelected
            );
public slots:
    //
    void catchLabelChanged(
            const QString& _name
            );
    //
    void catchSelected(
            bool _selected
            );

private:
    //
    Node* m_node;
};

#endif // NODEANTENNA_H
