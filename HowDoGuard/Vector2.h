#pragma once

#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include "GameObject.h"
#include "functions.h"

class Vector2;

typedef Vector2 Point;
typedef Vector2 Size;

class Vector2
    : public GameObject
{
private:

public:

    static Vector2
        ZERO,
        ONE,
        NEGATIVE_ONE;

    float
        X,
        Y;

    Vector2( void );
    Vector2( float x, float y );
    Vector2( float both );
    virtual ~Vector2( void );

    virtual string toString( void ) const;

    float distanceTo( Vector2 other );
    float directionToDeg( Vector2 other );
    float directionToRad( Vector2 other );

    const Vector2 operator+( const Vector2 &rhs ) const;
    const Vector2 operator-( const Vector2 &rhs ) const;
    const Vector2 operator*( float value ) const;
    const Vector2 operator/( float value ) const;

    Vector2 &operator+=( const Vector2 &rhs );
    Vector2 &operator-=( const Vector2 &rhs );
    Vector2 &operator*=( float value );
    Vector2 &operator/=( float value );
    Vector2 &operator= ( const Vector2 &rhs );

    bool operator==( const Vector2 &rhs ) const;
    bool operator!=( const Vector2 &rhs ) const;

};

#endif