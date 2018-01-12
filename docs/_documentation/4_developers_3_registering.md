---
title: "Load your generator into Porcupine"
excerpt: "Register your generator in the CodeEditor"
layout: single
author_profile : false
categories:
  - 4. Developers
permalink: /documentation/developers/registering
---

Once the code generator is written, it needs to be loaded into Porcupine before
it will produce code for your new package. This can be done by editing the [CodeEditor file](https://github.com/TimVanMourik/Porcupine/blob/master/src/CodeEditor/CodeEditor.cpp).
The most basic setup should
- Notify the program that there is a new language called "Squirrel"
- Add a new QTextEdit and put that in a new tab
- Attach the SquirrelGenerator

This can all be done by making a simple function `setupSquirrelEditor()` to take
care of this:
```
void CodeEditor::setupSquirrelEditor(
        )
{
  QString squirrel("Squirrel");
  m_programmingLanguages << squirrel;
  QTextEdit* squirrelEditor = new QTextEdit(this);
  m_textEditors[squirrel] = squirrelEditor;
  m_codeGenerators[squirrel] = new SquirrelGenerator(this);
  addTab(m_textEditors[squirrel], squirrel);
}
```

It should be noted that this setup is only required when there is at least one
Squirrel node in the editor. So it is advised to add the following to the
`CodeEditor::generateCode()` function:

```
language = "Squirrel";
if(isPresentInEditor(language, _nodeList))
{
  if(!m_textEditors[language])
  {
    setupSquirrelEditor();
  }
  ...
}
```

In the next section we will show how to take care of the layout of the code
editor.
