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

#ifndef NODETREEMODEL_H
#define NODETREEMODEL_H

#include <QList>
#include <QMap>
#include <QScrollArea>
#include <QStandardItemModel>

class Node;
class NodeTreeItem;
class CodeEditor;
class QDomDocument;
class QDomElement;
class QVBoxLayout;

class NodeTreeEditor : public QWidget
{
    Q_OBJECT
public:
    //
    NodeTreeEditor(
            QWidget* _parent = 0
            );
    //
    void addNode(
            Node* _node
            );
    //
    void removeNode(
            const Node* _node
            );
    //
    void saveToJson(
            QJsonObject& o_json
            ) const;
    //
    void setCodeEditor(
            CodeEditor* _editor
            );
    //
    void generateCode(
            );
    //
    void updateNodeOrder(
            );
    //
    void moveToNewLocation(
            );
    //
    const QList<NodeTreeItem*>& getNodeList(
            ) const;
    //
    ~NodeTreeEditor(
            );
public slots:
    /// @brief receives signal that _item just swapped places, so the nodes need to be reordered.
    void nodeMoved(
            NodeTreeItem* _item
            );
    /// @when a new link is created, the node list needs to be checkd for correctness and perhaps restructured
    void linkCreated(
            const Node* _from,
            const Node* _to
            );
private:
    //
    QVBoxLayout* m_layout;
    //
    QVector<const Node*> m_nodes;
    //
    QList<NodeTreeItem*> m_nodeList;
    //
    CodeEditor* m_codeEditor;
    //
    NodeTreeItem* getNodeTreeItem(
            const Node* _node
            );
    //
    QVector<NodeTreeItem*> getNodeTreeItems(
            QVector<const Node*> _nodes
            );
    //
    int nodeIndexInList(
            const Node* _node
            );
    //
    QList<int> nodeIndexInList(
            QVector<const Node*> _nodes
            );
};

#endif // NODETREEMODEL_H
