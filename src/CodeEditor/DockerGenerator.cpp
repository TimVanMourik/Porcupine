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

#include <QDebug>
#include <QFile>

#include "DockerGenerator.hpp"
#include "PortPair.hpp"

const QString DockerGenerator::s_thisLanguage("Docker");

DockerGenerator::DockerGenerator(
        CodeEditor* _editor
        ) :
    CodeGenerator(_editor)
{
}

QString DockerGenerator::generateCode(
            const QList<NodeTreeItem*>& _nodeList,
            const QVector<const Link*>& _linkList
            )
{
    Q_UNUSED(_linkList);
    QString code("");

    QStringList dockerModules;
    QStringList dockerModuleFiles;
    foreach (const NodeTreeItem* item, _nodeList)
    {
        QJsonObject json = item->getJson();
        Argument title(json["title"].toObject());
        QStringList dockerArguments = title.getArgument(s_thisLanguage)["name"].remove(' ').split(',');
        foreach (QString dockerArgument, dockerArguments)
        {
            if(!dockerArgument.isEmpty() && !dockerModules.contains(dockerArgument))
            {
                dockerModules << dockerArgument;
                QString file = QString(":/dictionaries/Neurodocker/%1.txt").arg(dockerArgument);
                if(QFile(file).exists())
                {
                    dockerModuleFiles << file;
                }
            }
        }
    }
    if(dockerModuleFiles.length() == 0)
    {
        return code;
    }

    QString preambleFile(":/dictionaries/Neurodocker/preamble.txt");
    QFile preamble(preambleFile);
    preamble.open(QIODevice::ReadOnly);
    code += preamble.readAll();
    preamble.close();

    foreach(QString module, dockerModuleFiles)
    {
        QFile file(module);
        file.open(QIODevice::ReadOnly);
        code += file.readAll();
        file.close();
    }

    QString postambleFile(":/dictionaries/Neurodocker/postamble.txt");
    QFile postamble(postambleFile);
    postamble.open(QIODevice::ReadOnly);
    code += postamble.readAll();
    postamble.close();

    return code;
}

DockerGenerator::~DockerGenerator()
{
}
