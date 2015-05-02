#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>

class DataType
{
public:
    DataType(
            const QString& _typeName
            );
    const QString& getName(
            ) const;
private:
    QString m_typeName;
};

#endif // DATATYPE_H
