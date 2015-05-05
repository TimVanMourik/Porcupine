#ifndef TREEITEM_H
#define TREEITEM_H

#include <QStandardItem>

class PortPair;

class FileNameItem : public QStandardItem
{
public:
    //
    enum {
        Type = QStandardItem::UserType + 0
    };
    //
    FileNameItem(
            const QString& _name
            );
    //
    void setPort(
            PortPair* _port
            );
    //
    void hasFileName(
            bool _bool
            );
    //
    int type(
            ) const;
    //
    ~FileNameItem(
            );
private:
    //
    PortPair* m_port;
};

#endif // TREEITEM_H
