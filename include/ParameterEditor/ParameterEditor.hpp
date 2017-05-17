#ifndef PARAMETEREDITOR_HPP
#define PARAMETEREDITOR_HPP

#include <QObject>
#include <QTableWidget>

class ParameterEditor : public QTableWidget
{
    Q_OBJECT
public:
    ParameterEditor(
            QWidget* _parent = 0
            );
    //
    QMap<QString, QString> getParameters(
            );
public slots:
    //
    void checkForEmptyRows(
            QTableWidgetItem* _item
            );
};

#endif // PARAMETEREDITOR_HPP
