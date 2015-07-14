#include "Argument.hpp"

Argument::Argument(
        const QString& _argumentName
        ) :
    m_argumentName(_argumentName)
{
}

void Argument::setName(
        const QString& _name
        )
{
    m_argumentName = _name;
}

const QString& Argument::getName(
        ) const
{
    return m_argumentName;
}

void Argument::addFunctionCode(
        QString _language,
        QString _function
        )
{
    FunctionCode code;
    code.language = _language;
    code.function = _function;
    m_functionCode.append(code);
}

void Argument::addArgumentCode(
        QString _language,
        QString _function
        )
{
    ArgumentCode code;
    code.language = _language;
    code.function = _function;
    m_argumentCode.append(code);
}

//const QVector<const DataType*>& Argument::getType(
//        ) const
//{
//    return m_type;
//}
