#include "Argument.hpp"

Argument::Argument(
        const QString& _argumentName,
        const QVector<const DataType*> _dataType
        ) :
    m_argumentName(_argumentName),
    m_type(_dataType)
{
}

const QString& Argument::getName(
        ) const
{
    return m_argumentName;
}

const QVector<const DataType*>& Argument::getType(
        ) const
{
    return m_type;
}
