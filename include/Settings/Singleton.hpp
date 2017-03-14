/*  Copyright (C) Tim van Mourik, 2014-2016
    Copyright (C) Tim van Mourik, 2017, DCCN
    All rights reserved

 This file is part of the Porcupine pipeline tool, see
 https://github.com/TimVanMourik/Porcupine for the documentation and
 details.

    This toolbox is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the fmri analysis toolbox. If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Singleton.h
/// @author Tim van Mourik
/// @date 8 January 2014
/// @brief
/// 1. http://stackoverflow.com/questions/86582/singleton-how-should-it-be-used
/// 2. http://www.codeproject.com/Articles/4750/Singleton-Pattern-A-review-and-analysis-of-existin
//----------------------------------------------------------------------------------------------------------------------

///@todo make the Singleton class thread-safe (source 2)

template <typename T>
class Singleton
{
public:
    //
    static T& getInstance(
                );
    //
    static void destroy();
protected:
    // Private Constructor
    Singleton();
    // Stop the compiler generating methods of copy the object
    Singleton(
            Singleton const& _copy
            ); // Not Implemented
    //
    Singleton& operator=(
            Singleton const& _copy
            ); // Not Implemented

    //
//    virtual ~Singleton();
private:
    //
    static T* s_instance;
};


template <typename T> T* Singleton<T>::s_instance = 0;

template <typename T>
Singleton<T>::Singleton()
{
    Singleton::s_instance = static_cast<T*> (this);
}

template <typename T>
T& Singleton<T>::getInstance()
{
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    if(!s_instance)
    {
        s_instance = new T();
    }
    return *(s_instance);
}

template <typename T>
void Singleton<T>::destroy()
{
    if(Singleton::s_instance)
    {
        delete s_instance;
        Singleton::s_instance = 0;
    }
}

#endif // SINGLETON_HPP
