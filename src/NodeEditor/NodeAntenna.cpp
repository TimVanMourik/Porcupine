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

#include "Node.hpp"
#include "NodeAntenna.hpp"

NodeAntenna::NodeAntenna(
        ) :
    QObject(0)
{

}

void NodeAntenna::setNode(
        Node* _node
        )
{
    m_node = _node;
}

void NodeAntenna::catchLabelChanged(
        const QString& _name
        )
{
    m_node->labelNameChanged(_name);
}


void NodeAntenna::catchSelected(
        bool _selected
        )
{
    m_node->setSelected(_selected);
}

void NodeAntenna::sendLabelChanged(
        const QString& _name
        )
{
    emit nodeNameChanged(_name);
}

void NodeAntenna::sendNodeSelected(
        bool _isSelected
        )
{
    emit nodeSelected(_isSelected);
}
