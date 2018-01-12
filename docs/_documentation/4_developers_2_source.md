---
title: "The source files"
excerpt: "Generator specific C++ header and source files"
layout: single
author_profile : false
categories:
  - 4. Developers
permalink: /documentation/developers/source
---

We will here follow an example of adding the hypothetical package Squirrel to
Porcupine, as they are good old friends. Squirrel is a Python package for
conducting some nutty analysis. The first thing we'll want to do is to create a
source-header pair of C++ files in the CodeEditor section.
The SquirrelGenerator.hpp goes into the [header directory](https://github.com/TimVanMourik/Porcupine/tree/master/include/CodeEditor),
the SquirrelGenerator.cpp will be placed in the [source directory](https://github.com/TimVanMourik/Porcupine/tree/master/source/CodeEditor).
We will here assume some familiarity with the standards of a C++ class
definition. In the header file, it is advised that you just copy an existing
generator and change the names from (e.g.) DockerGenerator to SquirrelGenerator.

There is a standard (empty) constructor and destructor method that we will not
touch, and there is a variable that states to what language we want to respond,
`static const QString s_thisLanguage;`. Lastly, the important part is that every
Generator has a `generateCode` function:
```
QString generateCode(
        const QList<NodeTreeItem*>& _nodeList,
        const QVector<const Link*>& _linkList = QVector<const Link*>(0)
        );
```

The output of this function will be all the code that you generate (in a
`QString`), the input will be the set of all Nodes and Links in the workflow
editor. Let's move to the cpp source file and implement the respective parts.

### The source file
We will not discuss the C++ specific includes and immediately go to the
Porcupine specific part. A good start would be to define the language that we
are programming for:
```
const QString SquirrelGenerator::s_thisLanguage("Squirrel");
```
We are going to use this variable to select only the Squirrel nodes from the
workflow. The standard constructor and destructor need to be present in the
cpp-file, but can be left empty. The only function we need to implement is the
`generateCode` function. If you want, you can make as many helper functions as
you want, but we here limit the scope to a single function.

In all likelihood, you want to loop over all nodes in the editor, and add code
for each of them:
```
QString SquirrelGenerator::generateCode(
        const QList<NodeTreeItem*>& _nodeList,
        const QVector<const Link*>& _linkList
        )
{
  QString code;
  foreach(const NodeTreeItem* item, _nodeList)
  {
      code += ...
  }
  return code;
}
```
What it is that you'd like to add is entirely up to you! But it is important
that you can access the variables in the node. Most of the variables are just
represented as JSON files. So we can for example take the title of the node in
this way:
```
foreach(const NodeTreeItem* item, _nodeList)
{
  QJsonObject json = _item->getJson();
  Argument title(json["title"].toObject());
  ...
}
```
The `Argument` is an internal structure that lets you easily access all
variables, so now we can access `title.m_name` that will yield a `QString`
that states the title of the node (e.g. squirrel.nut_cracker.py).

Almost identically, one can access all input and output ports:
```
foreach (const PortPair* pair,  _item->getPorts())
{
  Argument argument = pair->getArgument();
  code += argument.m_isInput      // e.g. true
  code += argument.m_isOutput     // e.g. false
  code += argument.m_argumentName // e.g. chestnut
  code += argument.m_isIterator   // e.g. true
}
```

From here on, it is entirely up to you what type of code you want to write! We
do need to cover how to install our SquirrelGenerator to Porcupine. This is
explained in the next chapter.
