#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <QString>
#include <QVector>

class DataType;

class Argument
{
public:
    Argument(
            const QString& _argumentName,
            const QVector<const DataType*> _dataType
            );

    const QString& getName(
            ) const;

    const QVector<const DataType*>& getType(
            ) const;

private:
    QString m_argumentName;
    const QVector<const DataType*> m_type;
};

#endif // ARGUMENT_HPP
