/*
 * Copyright (C) 2014 Tim van Mourik
*/

#ifndef NODESETTING_H
#define NODESETTING_H

//----------------------------------------------------------------------------------------------------------------------
/// @file NodeSetting.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <QStringList>
#include <QColor>

#include "Argument.hpp"

class NodeSetting
{
public:
    //
    NodeSetting(
            const Argument& _name,
            const QVector<Argument>& _ports
            );
    //
    void setColour(
            const QColor& _colour
              );
    //
    const QString& getName(
            ) const;
    //
    const Argument& getTitle(
            ) const;
    //
    const QVector<Argument>& getPorts(
            ) const;
    //
    void setCategory(
            const QStringList& _category
            );
    //
    const QStringList& getCategory(
            ) const;
    //
    ~NodeSetting(
            );
private:
    //
    Argument m_name;
    //
    QVector<Argument> m_ports;
    //
    QStringList m_category;
    //
    QColor m_nodeColour;
};

#endif // NODESETTING_H
