#include "DataType.hpp"

DataType::DataType(
        const QString& _typeName
        ) :
    m_typeName(_typeName)
{
}

const QString& DataType::getName(
        ) const
{
    return m_typeName;
}
