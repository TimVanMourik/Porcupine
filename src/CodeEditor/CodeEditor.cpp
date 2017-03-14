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

#include <QTextEdit>

#include "CodeEditor.hpp"
#include "CodeGenerator.hpp"
#include "BashHighlighter.hpp"
#include "MatlabHighlighter.hpp"
#include "PythonHighlighter.hpp"
#include "FslGenerator.hpp"
#include "TvmGenerator.hpp"
#include "SpmGenerator.hpp"
#include "PythonGenerator.hpp"

CodeEditor::CodeEditor(
        QWidget* _parent
        ) :
    QTabWidget(_parent)
{
    //TVM within MATLAB (C)
    setupMatlabEditor();
    //SPM within MATLAB (C)
    setupSpmEditor();
    //Bash
    setupBashEditor();
    //Python
    setupPythonEditor();
}

void CodeEditor::generateCode(
        const QList<NodeTreeItem*>& _nodeList,
        const QVector<const Link*>& _linkList
        )
{
    foreach(QString language, m_programmingLanguages)
    {
        m_textEditors[language]->setPlainText(m_codeGenerators[language]->generateCode(_nodeList, _linkList));
    }
}

void CodeEditor::setupMatlabEditor(
        )
{
    /// @todo put tabWidth in the preferences
    const int tabWidth = 4;
    QString matlab("MATLAB - TVM");
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

void CodeEditor::setupSpmEditor(
        )
{
    const int tabWidth = 4;
    QString spm("MATLAB - SPM");
    m_programmingLanguages << spm;
    QFont matlabFont = QFont("Courier", 10);
    matlabFont.setStyleHint(QFont::Monospace);
    matlabFont.setFixedPitch(true);
    QFontMetrics matlabMetric(matlabFont);

    QTextEdit* spmEditor = new QTextEdit(this);
    spmEditor->setFont(matlabFont);
    spmEditor->setTabStopWidth(tabWidth * matlabMetric.width(' '));

    new MatlabHighlighter(spmEditor->document());
    m_textEditors[spm] = spmEditor;
    m_codeGenerators[spm] = new SpmGenerator();
    addTab(m_textEditors[spm], spm);
}

void CodeEditor::setupBashEditor(
        )
{
    const int tabWidth = 4;
    QString bash("Bash");
    m_programmingLanguages << bash;
    QFont bashFont = QFont("Courier", 10);
    bashFont.setStyleHint(QFont::Monospace);
    bashFont.setFixedPitch(true);
    QFontMetrics bashMetric(bashFont);

    QTextEdit* bashEditor = new QTextEdit(this);
    bashEditor->setFont(bashFont);
    bashEditor->setTabStopWidth(tabWidth * bashMetric.width(' '));

    new BashHighlighter(bashEditor->document());
    m_textEditors[bash] = bashEditor;
    m_codeGenerators[bash] = new FslGenerator();
    addTab(m_textEditors[bash], bash);
}

void CodeEditor::setupPythonEditor(
        )
{
    const int tabWidth = 4;
    QString python("Python");
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
    m_codeGenerators[python] = new PythonGenerator();
    addTab(m_textEditors[python], python);
}

CodeEditor::~CodeEditor()
{

}

