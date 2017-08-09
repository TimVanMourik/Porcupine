#ifndef NIPYPESTUPIDEXCEPTIONS_HPP
#define NIPYPESTUPIDEXCEPTIONS_HPP

#include "Singleton.hpp"
#include "NipypeGenerator.hpp"
#include "Link.hpp"

class NipypeStupidExceptions : public Singleton<NipypeStupidExceptions>
{
    friend class Singleton<NipypeStupidExceptions>;

public:
    //
    QString exceptionNodetoCode(
            const NodeTreeItem* _item,
            const QMap<QString, QString>& parameters
            ) const;
    //
    QString codeForIdentityInterface(
            const NodeTreeItem* _item,
            const QMap<QString, QString>& parameter
            ) const;
    //
    QString codeForSelectFiles(
            const NodeTreeItem* _item,
            const QMap<QString, QString>& parameter
            ) const;
    //
    QString codeForMySQLSink(
            const NodeTreeItem* _item,
            const QMap<QString, QString>& parameter
            ) const;
    //
    QString codeForSQLiteSink(
            const NodeTreeItem* _item,
            const QMap<QString, QString>& parameter
            ) const;
    //
    QString codeForS3DataGrabber(
            const NodeTreeItem* _item,
            const QMap<QString, QString>& parameter
            ) const;


NipypeStupidExceptions(
        );
/// @brief
NipypeStupidExceptions(
        NipypeStupidExceptions const& _copy
        ); //Not implemented
/// @brief
NipypeStupidExceptions& operator=(
        NipypeStupidExceptions const& _copy
        ); //Not implemented
/// @brief
~NipypeStupidExceptions(
        );

private:
    //
    QStringList getMapNodeFields(
            const NodeTreeItem* _item
            ) const;
    //
    static const QString s_thisLanguage;
};

#endif // NIPYPESTUPIDEXCEPTIONS_HPP
