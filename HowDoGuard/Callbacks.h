#pragma once

#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include "Common.h"
#include "GameObject.h"

template <typename ReturnType, typename Param = void>
class Callback
    : public GameObject
{

    friend bool operator==( const Callback<ReturnType, Param>& lhs, const Callback<ReturnType, Param>& rhs ) { return lhs.equalTo(rhs); };
    friend bool operator!=( const Callback<ReturnType, Param>& lhs, const Callback<ReturnType, Param>& rhs ) { return !lhs.equalTo(rhs); };

protected:

    inline virtual bool equalTo( const Callback<ReturnType, Param>& rhs ) const { return false; };

public:

    virtual ReturnType invoke( Param param ) = 0;
    virtual Callback* clone( void ) = 0;
    virtual bool isMethodOf( void* object) = 0;

};

template <typename ReturnType, typename Param = void>
class StaticFunctionCallback
    : public Callback<ReturnType, Param>
{
protected:

    virtual bool equalTo( const Callback<ReturnType, Param>& rhs ) const
    {
        if ( const StaticFunctionCallback<ReturnType, Param>* convert = dynamic_cast<const StaticFunctionCallback<ReturnType, Param>*>(&rhs) )
        {
            return ( _function == convert->_function );
        }
        return false;
    }

private:

    ReturnType 
        (*_function)(Param);

public:

    StaticFunctionCallback(ReturnType (*function)(Param))
    {
        _function = function;
    }

    inline virtual ReturnType invoke(Param param) { return (*_function)(param); }
    inline virtual StaticFunctionCallback* clone( void ) { return New StaticFunctionCallback(_function); }
    inline virtual bool isMethodOf( void* object ) { return false; }
    inline virtual string toString( void ) const { return "Static Function Callback"; };

};

template <typename ReturnType, typename Param = void, typename ObjectType = void, typename Method = void>
class MethodCallback
    : public Callback<ReturnType, Param>
{
protected:

    virtual bool equalTo( const Callback<ReturnType, Param>& rhs ) const
    {
        if ( const MethodCallback<ReturnType, Param, ObjectType, Method>* convert = dynamic_cast<const MethodCallback<ReturnType, Param, ObjectType, Method>*>(&rhs) )
        {
            return ( _object == convert->_object && _method == convert->_method );
        }
        return false;
    }

private:

    void* 
        _object;

    Method 
        _method;

public:

    MethodCallback( void* object, Method method )
    {
        _object = object;
        _method = method;
    }

    inline virtual ReturnType invoke( Param param ) { return (static_cast<ObjectType*>(_object)->*_method)(param); }
    inline virtual MethodCallback* clone( void )    { return New MethodCallback(_object, _method); }
    inline virtual bool isMethodOf( void* object )    { return _object == object; }
    inline virtual string toString( void ) const    { return "Method Callback"; };

};

#endif