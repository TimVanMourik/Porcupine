#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <QMap>
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
    QString getArgument(
            const QString& _language
            ) const;
    //
    QString getComment(
            const QString& _language
            ) const;
    //
    unsigned int numberOfCodeRules(
            );
    //
    void addCode(
            const QString& _language,
            const QString& _argument,
            const QString& _comment = QString("")
            );
    //
//    const QVector<const DataType*>& getType(
//            ) const;

private:
    //
    QString m_argumentName;
    //
    struct Code
    {
        QString argument;
        QString comment;
    };
    //
    QMap<QString, Code> m_code;
    //
//    const QVector<const DataType*> m_type;

};

#endif // ARGUMENT_HPP
