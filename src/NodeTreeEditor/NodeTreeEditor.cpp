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

#include <assert.h>

#include <QDropEvent>
#include <QMimeData>
#include <QPropertyAnimation>
#include <QVBoxLayout>

#include "CodeEditor.hpp"
#include "NodeTreeItem.hpp"
#include "NodeTreeEditor.hpp"

#include <QPushButton>

#include <QLabel>
NodeTreeEditor::NodeTreeEditor(
        QWidget* _parent
        ) :
    QWidget(_parent),
    m_layout(0),
    m_codeEditor(0)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QScrollArea* area = new QScrollArea;
    layout->addWidget(area);

    QWidget* contents = new QWidget;
    m_layout = new QVBoxLayout(contents);
    m_layout->setAlignment(Qt::AlignTop);
    area->setWidget(contents);

    area->setFrameShadow(QFrame::Raised);
    area->setFrameStyle(QFrame::StyledPanel);
    area->setWidgetResizable(true);
}

void NodeTreeEditor::addNode(
        const Node* _node
        )
{
    m_nodes.append(_node);
    NodeTreeItem* item = new NodeTreeItem(_node, this);

    m_layout->addWidget(item);
    m_nodeList.append(item);
    item->setNumber(m_nodeList.length());

    connect(item, SIGNAL(moved(NodeTreeItem*)), this, SLOT(nodeMoved(NodeTreeItem*)));
}

void NodeTreeEditor::removeNode(
        const Node* _node
        )
{
    assert(_node != 0);
    NodeTreeItem* item = getNodeTreeItem(_node);
    assert(item != 0);
    m_nodes.removeOne(_node);
    m_nodeList.removeOne(item);
    delete item;
    updateNodeOrder();
}

void NodeTreeEditor::setCodeEditor(
        CodeEditor* _editor
        )
{
    m_codeEditor = _editor;
}

void NodeTreeEditor::generateCode(
        )
{
    m_codeEditor->generateCode(m_nodeList);
}

//#include <iostream>
//const static int initialSpacing = 13;
//const static int nodeSpacing = 15;
void NodeTreeEditor::moveToNewLocation()
{
//    int startingHeight = initialSpacing;
//    int x, y, w, h;
//    foreach (NodeTreeItem* item, m_nodeList)
//    {
//        item->geometry().getRect(&x, &y, &w, &h);
//        y = startingHeight;
//        item->setGeometry(x, y, w, h);
//        startingHeight += h + nodeSpacing;

//        QPropertyAnimation* animation = new QPropertyAnimation(item, "geometry");
//        animation->setDuration(400);

//        item->setVisible(true);
//        QRect start = QRect(x, item->getStartPosition().y(), w, h);
//        QRect stop  = QRect(x, item->pos().y(), w, h);
//        animation->setStartValue(start);
//        animation->setEndValue(stop);

//        item->setGeometry(start);
////        m_hider.unhide(item);

//        animation->start();
//    }
}

void NodeTreeEditor::nodeMoved(
        NodeTreeItem* _item
        )
{
    //remove the current _item
    m_nodeList.removeOne(_item);
    m_layout->removeWidget(_item);

    //The node needs to be placed after the last ancestor...
    NodeTreeItem* lastAncestor = 0;
    int begin = 0;
    for(int i = 0; i < m_nodeList.length(); ++i)
    {
        if(m_nodeList[i]->isAncestorOf(_item))
        {
            lastAncestor = m_nodeList[i];
        }
    }
    if(lastAncestor)
    {
        begin = m_nodeList.indexOf(lastAncestor) + 1;
    }

    NodeTreeItem* firstChild = 0;
    int end = m_nodeList.length();
    //...and before the first child
    for(int i = begin; i < end; ++i)
    {
        if(_item->isAncestorOf(m_nodeList[i]))
        {
            firstChild = m_nodeList[i];
            break;
        }
    }
    if(firstChild)
    {
        end = m_nodeList.indexOf(firstChild);
    }
    int index = end;

    if(begin != end) //if begin == end then it's pretty clear where our node should be
    {
        for(int i = begin; i < end; i++)
        {
            //if the item is placed above me, then insert here
            if(m_nodeList[i]->y() > _item->y())
            {
                index = i;
                break;
            }
        }
    }
    m_nodeList.insert(index, _item);
    m_layout->insertWidget(index, _item);

    /// @todo animate the following updates
    updateNodeOrder();
    moveToNewLocation();
}

void NodeTreeEditor::saveToXml(
        QDomElement& _xmlElement
        ) const
{
    foreach(const NodeTreeItem* node, m_nodeList)
    {
        node->saveToXml(_xmlElement);
    }
}

void NodeTreeEditor::updateNodeOrder(
        )
{
    for(int i = 0; i < m_nodeList.length(); ++i)
    {
        m_nodeList[i]->setNumber(i + 1);
    }
}

void NodeTreeEditor::linkCreated(
        const Node* _from,
        const Node* _to
        )
{
    int toIndex = nodeIndexInList(_to);
    int fromIndex = nodeIndexInList(_from);
    if(fromIndex < toIndex)
    {
        //the list is already in the right order
        return;
    }
    QVector<const Node*> _descendants = m_nodeList[toIndex]->getDescendants();
    _descendants.prepend(_to);

    QVector<NodeTreeItem*> descendantItems = getNodeTreeItems(_descendants);
    QList<int> childIndices = nodeIndexInList(_descendants);

    int positioningIndex = std::max(fromIndex, childIndices.length() - 1);
    ///@todo find a less drastic solution
    for(int i = 0; i < childIndices.length(); ++i)
    {
        m_nodeList.removeOne(descendantItems[i]);
        m_layout->removeWidget(descendantItems[i]);

        m_nodeList.insert(positioningIndex, descendantItems[i]);
        m_layout->insertWidget(positioningIndex, descendantItems[i]);
    }
    updateNodeOrder();
}

NodeTreeItem* NodeTreeEditor::getNodeTreeItem(
        const Node* _node
        )
{
    return m_nodeList[nodeIndexInList(_node)];
}

QVector<NodeTreeItem*> NodeTreeEditor::getNodeTreeItems(
        QVector<const Node*> _nodes
        )
{
    QVector<NodeTreeItem*> list(_nodes.length());
    for(int i = 0; i < _nodes.length(); ++i)
    {
        list[i] = m_nodeList[nodeIndexInList(_nodes[i])];
    }
    return list;
}

int NodeTreeEditor::nodeIndexInList(
        const Node* _node
        )
{
    for(int i = 0; i < m_nodeList.length(); ++i)
    {
        if(m_nodeList[i]->getNode() == _node)
        {
            return i;
        }
    }
    // If we cannot find the Node
    return -1;
}

QList<int> NodeTreeEditor::nodeIndexInList(
        QVector<const Node*> _nodes
        )
{
    QList<int> indices;
    for(int i = 0; i < _nodes.length(); ++i)
    {
        indices.append(nodeIndexInList(_nodes[i]));
    }
    std::sort(indices.begin(), indices.end());
    return indices;
}


const QList<NodeTreeItem*>& NodeTreeEditor::getNodeList(
        ) const
{
    return m_nodeList;
}

NodeTreeEditor::~NodeTreeEditor(
        )
{
    foreach (NodeTreeItem* item, m_nodeList)
    {
        delete item;
    }
}

