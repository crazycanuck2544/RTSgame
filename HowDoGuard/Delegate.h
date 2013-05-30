#pragma once

#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include "Common.h"
#include "GameObject.h"

#include "Callbacks.h"

template <typename ReturnType, typename Param = void>
class Delegate
    : public GameObject
{
private:

    Callback<ReturnType, Param> 
        *_callback;

public:

    Delegate(ReturnType (*function)(Param))
    {
        _callback = New StaticFunctionCallback<ReturnType, Param>(function);
    }

    template <typename ObjectType, typename Method>
    Delegate(ObjectType* object, Method method)
    {
        _callback = New MethodCallback<ReturnType, Param, ObjectType, Method>(object, method);
    }

    virtual string toString( void ) const { return "Delegate"; }

    void setFunction( ReturnType (*function)(Param))
    {
        if (_callback != nullptr)
            delete _callback;
        _callback = New StaticFunctionCallback<ReturnType, Param>(function);
    }

    template <typename ObjectType, typename Method>
    void setFunction( ObjectType* object, Method method )
    {
        if (_callback != nullptr)
            delete _callback;
        _callback = New MethodCallback<ReturnType, Param, ObjectType, Method>(object, method);
    }

    Delegate( const Delegate<ReturnType, Param>& rhs )
    {
        _callback = rhs._callback->clone();
    }

    Delegate<ReturnType, Param> operator=( const Delegate<ReturnType, Param>& rhs )
    {
        if ( _callback != nullptr )
            delete _callback;
        _callback = rhs._callback->clone();
        return *this;
    }

    inline ReturnType operator()( Param param ) { return _callback->invoke(param); }

    bool isMethodOf( void* object )
    {
        if ( _callback == nullptr )
            return false;
        return _callback->isMethodOf(object);
    }

    inline ReturnType invoke( Param param ) { return _callback->invoke(param); }

    ~Delegate() { if ( _callback != nullptr ) { delete _callback; _callback = nullptr; } }

    bool operator==(const Delegate<ReturnType, Param>& rhs)
    {
        if (_callback == rhs._callback)
            return true;

        if (_callback == nullptr || rhs._callback == nullptr)
            return false;

        return ( *(_callback) == *(rhs._callback) );
    }

    bool operator!=(const Delegate<ReturnType, Param>& rhs)
    {
        if (_callback == rhs._callback)
            return false;

        if (_callback == nullptr || rhs._callback == nullptr)
            return true;

        return ( *(_callback) != *(rhs._callback) );
    }
};

#endif