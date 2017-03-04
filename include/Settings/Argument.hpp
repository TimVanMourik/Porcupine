#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <QMap>
#include <QString>
#include <QVector>

class DataType;

class Argument
{
public:
    enum FieldType
    {
        NONE    = 0,
        INPUT   = 1,
        OUTPUT  = 2,
        INOUT   = 3,
        HIDDEN  = 4, //hidden in the NodeEditor
        SECRET  = 5  //also hidden in the NodeTreeEditor
    };
    //
    Argument(
            const QString& _argumentName = QString(),
            FieldType _type = NONE,
            QString _defaultValue = QString("")
            );
    //
    bool isEditable(
            ) const;
    //
    void setName(
            const QString& _name
            );
    //
    void setDefault(
            const QString& _name
            );
    //
    void setEditable(
            bool _editable
            );
    //
    void setType(
            const FieldType& _type
            );
    //
    const QString& getName(
            ) const;
    //
    const QString& getDefault(
            ) const;
    //
    const FieldType& getType(
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
    FieldType m_portType;
    //
    QString m_argumentName;
    //
    QString m_defaultValue;
    //
    bool m_isEditable;
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
