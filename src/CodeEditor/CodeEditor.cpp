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

#include <QFileDialog>
#include <QTextEdit>

#include "CodeEditor.hpp"
#include "CodeGenerator.hpp"
#include "BashHighlighter.hpp"
#include "MatlabHighlighter.hpp"
#include "PythonHighlighter.hpp"
#include "TvmGenerator.hpp"
#include "NipypeGenerator.hpp"
#include "ParameterEditor.hpp"

CodeEditor::CodeEditor(
        QWidget* _parent
        ) :
    QTabWidget(_parent)
{
}

void CodeEditor::setParameterEditor(
        ParameterEditor* _editor
        )
{
    m_parameterEditor = _editor;
}


QMap<QString, QString> CodeEditor::getParameters(
        )
{
    return m_parameterEditor->getParameters();
}

bool CodeEditor::isPresentInEditor(
        const QString& _language,
        const QList<NodeTreeItem*>& _nodeList
        )
{
    foreach(const NodeTreeItem* item, _nodeList)
    {
        QJsonObject json = item->getJson();
        Argument title(json["title"].toObject());
        if(!title.getArgument(_language).isEmpty())
        {
            return true;
        }
    }
    return false;
}

void CodeEditor::generateCode(
        const QList<NodeTreeItem*>& _nodeList,
        const QVector<const Link*>& _linkList
        )
{
    QString language;
    language = "NiPype";
    if(isPresentInEditor(language, _nodeList))
    {
        if(!m_textEditors[language])
        {
            setupNipypeEditor();
        }
        m_textEditors[language]->setPlainText(m_codeGenerators[language]->generateCode(_nodeList, _linkList));

        QFile styleFile(":/qss/codeEditor.qss");
        styleFile.open(QFile::ReadOnly);
        QString translucentLabel = QString::fromLatin1(styleFile.readAll());
        m_textEditors[language]->setStyleSheet(translucentLabel);
    }

    language = "TvM";
    if(isPresentInEditor(language, _nodeList))
    {
        if(!m_textEditors[language])
        {
            setupTvmEditor();
        }
        m_textEditors[language]->setPlainText(m_codeGenerators[language]->generateCode(_nodeList, _linkList));

        QFile styleFile(":/qss/codeEditor.qss");
        styleFile.open(QFile::ReadOnly);
        QString translucentLabel = QString::fromLatin1(styleFile.readAll());
        m_textEditors[language]->setStyleSheet(translucentLabel);
    }
}

void CodeEditor::saveCodeToFile(
        )
{
    QTextEdit* currentTextEdit = (QTextEdit*) currentWidget();
    if(currentTextEdit)
    {
        QString fileName = QFileDialog::getSaveFileName();
        if (fileName.isEmpty())
        {
            return;
        }
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(currentTextEdit->toPlainText().toUtf8());
        }
        file.close();
    }
}

void CodeEditor::setupTvmEditor(
        )
{
    /// @todo put tabWidth in the preferences
    const int tabWidth = 4;
    QString matlab("TvM");
    m_programmingLanguages << matlab;
    QFont matlabFont = QFont("Courier", 10);
    matlabFont.setStyleHint(QFont::Monospace);
    matlabFont.setFixedPitch(true);
    QFontMetrics matlabMetric(matlabFont);

    QTextEdit* matlabEditor = new QTextEdit(this);
    matlabEditor->setFont(matlabFont);
    matlabEditor->setTabStopWidth(tabWidth * matlabMetric.width(' '));

    new MatlabHighlighter(matlabEditor->document());
    m_textEditors[matlab] = matlabEditor;
    m_codeGenerators[matlab] = new TvmGenerator();
    addTab(m_textEditors[matlab], matlab);
}


void CodeEditor::setupNipypeEditor(
        )
{
    const int tabWidth = 4;
    QString python("NiPype");
    m_programmingLanguages << python;
    QFont pythonFont = QFont("Courier", 10);
    pythonFont.setStyleHint(QFont::Monospace);
    pythonFont.setFixedPitch(true);
    QFontMetrics pythonMetric(pythonFont);

    QTextEdit* pythonEditor = new QTextEdit(this);
    pythonEditor->setFont(pythonFont);
    pythonEditor->setTabStopWidth(tabWidth * pythonMetric.width(' '));

    new PythonHighlighter(pythonEditor->document());
    m_textEditors[python] = pythonEditor;
    m_codeGenerators[python] = new NipypeGenerator(this);
    addTab(m_textEditors[python], python);
}

CodeEditor::~CodeEditor()
{
}

