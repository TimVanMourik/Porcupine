---
title: "Code editor layout"
excerpt: "Change layout and add syntax highlighting in your code"
layout: single
author_profile : false
categories:
  - 4. Developers
permalink: /documentation/developers/highlighter
---

In the previous section we discussed how to minimally install a new code
generator in Porcupine. But you might want to make the code look niced than
that. There are two main ways in which this can be done: editing the custom
parameters on the `QTextEdit` and adding a custom `QFont`, or to add syntax
highlighting. The first one is can take many forms but we here show on option
by example:

```
void CodeEditor::setupSquirrelEditor(
        )
{
  ...
  const int tabWidth = 4;
  QFont squirrelFont = QFont("Courier", 10);
  squirrelFont.setStyleHint(QFont::Monospace);
  squirrelFont.setFixedPitch(true);
  QFontMetrics squirrelMetric(squirrelFont);
  ...
  squirrelEditor->setFont(squirrelFont);
  squirrelEditor->setTabStopWidth(tabWidth * squirrelFont.width(' '));
  ...
}
```

The other option is to add a `SyntaxHighlighter`. We provide several default
highlighters, amongst which a PythonHighlighter. This can be add to the code
editor as easily as this single line:
```
void CodeEditor::setupSquirrelEditor(
        )
{
  ...
  new PythonHighlighter(squirrelEditor->document());
  ...
}
```
You could also write a custom highlighter. We will not discuss that here. We
anticipate that once you have reached the end of this documentation, you are
such an expert that you will easily do this by yourself. If not, please do get
in touch with us, because we would love to help you extend Porcupine!
