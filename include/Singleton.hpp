/*
 * Copyright (C) 2014 Tim van Mourik
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
