/*
 * Copyright (C) 2014 Tim van Mourik
*/

#ifndef NODELIBRARY_HPP
#define NODELIBRARY_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file NodeLibrary.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <map>

#include <QDomDocument>
#include <QString>
#include <QtXmlPatterns>

#include "Singleton.hpp"

class DataType;
class NodeSetting;

class NodeLibrary : public Singleton<NodeLibrary>
{
    friend class Singleton<NodeLibrary>;
public:
    /// @brief The scema is an .xsd file in which the schema for a node xml-file is explained
    /// @param _schema is not const because .open() is not a const function (even in read-only mode)
    void setDataTypeSchema(
            QFile& _schema
            );
    /// @brief The scema is an .xsd file in which the schema for a node xml-file is explained
    /// @param _schema is not const because .open() is not a const function (even in read-only mode)
    void setNodeSchema(
            QFile& _schema
            );
    /// @brief
    /// @param _schema is not const because .open() is not a const function (even in read-only mode)
    QString addNodeSetting(
            QFile& _node
            );
    /// @brief
    /// @param _schema is not const because .open() is not a const function (even in read-only mode)
    void addDataTypes(
            QFile& _type
            );
    /// @brief
    const NodeSetting* getNodeSetting(
            const QString& _nodeName
            ) /*const*/;
    /// @brief
    const QStringList& getNodeNames(
        ) const ;
    /// @brief
    const QStringList getCategory(
            const QString& _setting
            ) const;
    /// @brief
    void save(
            QDataStream&
            );

private:
    /// @brief
    QMap<QString, NodeSetting*> m_nodeSettings;
    /// @brief
    QMap<QString, DataType*> m_dataTypes;
    /// @brief
    QStringList m_nodeNames;
    /// @brief
    QStringList m_typeNames;
    /// @brief
    QXmlSchemaValidator* m_nodeValidator;
    /// @brief
    NodeLibrary(
            );
    /// @brief
    void parseCodeBlock(
            const QDomNode& _code,
            QString& o_language,
            QString& o_argument,
            QString& o_comment
            );
    /// @brief
    NodeLibrary(
            NodeLibrary const& _copy
            ); //Not implemented
    /// @brief
    NodeLibrary& operator=(
            NodeLibrary const& _copy
            ); //Not implemented
    /// @brief
    ~NodeLibrary(
            );
};

#endif // NODELIBRARY_HPP
