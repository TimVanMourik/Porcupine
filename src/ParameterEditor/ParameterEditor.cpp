#include <QHeaderView>
#include <QJsonObject>
#include <QJsonArray>

#include "ParameterEditor.hpp"

ParameterEditor::ParameterEditor(
        QWidget* _parent
        ) :
    QTableWidget(0, 2, _parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    setShowGrid(true);
    verticalHeader()->hide();

    QStringList labels;
    labels << tr("Parameter") << tr("Value");
    setHorizontalHeaderLabels(labels);

    int row = rowCount();
    insertRow(row);
    setItem(row, 0, new QTableWidgetItem("WorkingDirectory"));
    setItem(row, 1, new QTableWidgetItem("\"~/Porcupipelines/ThisStudy\""));

    insertRow(rowCount());

    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(checkForEmptyRows(QTableWidgetItem*)));
}

void ParameterEditor::saveToJson(
        QJsonObject& o_json
        )
{
    QJsonArray parameters;
    for(int i = 0; i < rowCount(); ++i)
    {
        QJsonObject keyValuePair;
        if(item(i, 0) && item(i, 1))
        {
            keyValuePair["key"]   = item(i, 0)->text();
            keyValuePair["value"] = item(i, 1)->text();
            parameters.append(keyValuePair);
        }
    }
    o_json["parameters"] = parameters;
}

void ParameterEditor::loadFromJson(
        const QJsonObject& _json
        )
{
    clear();
    QStringList labels;
    labels << tr("Parameter") << tr("Value");
    setHorizontalHeaderLabels(labels);
    int row = 0;
    foreach (QJsonValue keyValuePair, _json["parameters"].toArray())
    {
        QJsonObject keyValueObject = keyValuePair.toObject();
        setItem(row, 0, new QTableWidgetItem(keyValueObject[ "key" ].toString()));
        setItem(row, 1, new QTableWidgetItem(keyValueObject["value"].toString()));
        row++;
    }
}

QMap<QString, QString> ParameterEditor::getParameters(
        )
{
    QMap<QString, QString> parameters;
    for(int i = 0; i < rowCount() - 1; ++i)
    {
        QString key   = item(i, 0) ? item(i, 0)->text() : "";
        QString value = item(i, 1) ? item(i, 1)->text() : "";
        if(!key.isEmpty() && !value.isEmpty())
        {
            parameters[key] = value;
        }
    }
    return parameters;
}

void ParameterEditor::checkForEmptyRows(
        QTableWidgetItem* _item
        )
{
    if(_item->row() == rowCount() - 1 && !_item->text().isEmpty())
    {
        insertRow(rowCount());
        return;
    }

    // check if entire row is empty
    if(_item->row() != rowCount() - 1)
    {
        for(int j = 0; j < columnCount(); ++j)
        {
            if(!item(_item->row(), j) || item(_item->row(), j)->text().isEmpty())
            {
                if(j == columnCount() - 1)
                {
                    removeRow(_item->row());
                }
            }
            else
            {
                return;
            }
        }
    }
}






