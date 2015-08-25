#include "Argument.hpp"

Argument::Argument(
        const QString& _argumentName,
        FieldType _type
        ) :
    m_portType(_type),
    m_argumentName(_argumentName)
{
}

void Argument::setName(
        const QString& _name
        )
{
    m_argumentName = _name;
}

void Argument::setType(
        const FieldType& _type
        )
{
    m_portType = _type;
}

const QString& Argument::getName(
        ) const
{
    return m_argumentName;
}

const Argument::FieldType& Argument::getType(
        ) const
{
    return m_portType;
}

QString Argument::getArgument(
        const QString& _language
        ) const
{
    if(m_code.contains(_language))
    {
        return m_code[_language].argument;
    }
    else
    {
        return QString();
    }
}

QString Argument::getComment(
        const QString& _language
        ) const
{
    if(m_code.contains(_language))
    {
        return m_code[_language].comment;
    }
    else
    {
        return QString();
    }
}

void Argument::addCode(
        const QString& _language,
        const QString& _function,
        const QString& _comment
        )
{
    m_code[_language] = Code();
    m_code[_language].argument = _function;
    m_code[_language].comment  = _comment;
}

//const QVector<const DataType*>& Argument::getType(
//        ) const
//{
//    return m_type;
//}
