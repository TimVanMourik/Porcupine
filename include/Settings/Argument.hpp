#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <QString>
#include <QVector>

class DataType;

class Argument
{
public:
    //
    Argument(
            const QString& _argumentName = QString()
            );
    //
    void setName(
            const QString& _name
            );
    //
    const QString& getName(
            ) const;
    //
    void addFunctionCode(
            QString _language,
            QString _function
            );
    //
    void addArgumentCode(
            QString _language,
            QString _function
            );
    //
//    const QVector<const DataType*>& getType(
//            ) const;

private:
    //
    QString m_argumentName;
    //
    struct FunctionCode
    {
        QString language;
        QString function;
    };
    struct ArgumentCode
    {
        QString language;
        QString function;
    };
    QVector<ArgumentCode> m_argumentCode;
    QVector<FunctionCode> m_functionCode;
    //
//    const QVector<const DataType*> m_type;

};

#endif // ARGUMENT_HPP
