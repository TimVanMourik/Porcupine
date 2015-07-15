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
            const QVector<Argument>& _inputPortNames,
            const QVector<Argument>& _inOutPortNames,
            const QVector<Argument>& _outputPortNames
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
    const QVector<Argument>& getInput(
            ) const;
    //
    const QVector<Argument>& getInOut(
            ) const;
    //
    const QVector<Argument>& getOutput(
            ) const;
    //
    ~NodeSetting(
            );
private:
    //
    Argument m_name;
    //
    QVector<Argument> m_inputPortNames;
    //
    QVector<Argument>  m_inOutPortNames;
    //
    QVector<Argument>  m_outputPortNames;
    //
    QStringList m_matlabCode;
    //
    QColor m_nodeColour;
};

#endif // NODESETTING_H
