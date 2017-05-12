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
};

#endif // PARAMETEREDITOR_HPP
