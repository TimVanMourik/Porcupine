#include "FileNameItem.hpp"
#include "PortPair.hpp"

FileNameItem::FileNameItem(
        const QString& _name
        ) :
    QStandardItem(_name)
{
}

void FileNameItem::hasFileName(
        bool _bool
        )
{
    if(m_port)
    {
        m_port->hasFileName(_bool);
    }
}

void FileNameItem::setPort(
        PortPair* _port
        )
{
    m_port = _port;
}

int FileNameItem::type(
        ) const
{
    return Type;
}

FileNameItem::~FileNameItem(
        )
{

}

