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
    code += "docker run --rm kaczmarj/neurodocker generate \\\n";
    code += "--base timvanmourik/porcupine --pkg-manager apt \\\n";
    QStringList uniqueDockerCommands;
    foreach (const NodeTreeItem* item, _nodeList)
    {
        QJsonObject json = item->getJson();
        Argument title(json["title"].toObject());
        QString dockerArgument = title.getArgument(s_thisLanguage);
        if(!dockerArgument.isEmpty() && !uniqueDockerCommands.contains(dockerArgument))
        {
            uniqueDockerCommands << dockerArgument;
        }
    }
    foreach (const QString& command, uniqueDockerCommands)
    {
        code += command + " \\\n";
    }

    QString dockerFile("Dockerfile");
    code += QString("> %1\n\n").arg(dockerFile);

    code += "# Build Docker image using the saved Dockerfile.\n";
    code += QString("docker build -t myimage -f %1 .").arg(dockerFile);

    code += "\n";
    return code;
}

DockerGenerator::~DockerGenerator()
{
}
