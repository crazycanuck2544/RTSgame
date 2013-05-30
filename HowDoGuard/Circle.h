#pragma once

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "GameObject.h"
#include "Vector2.h"

class Rect;

class Circle :
    public GameObject
{
private:

public:

    static Circle
        ZERO,
        ONE;

    float 
        X,
        Y,
        Radius;

    Circle( void );
    Circle( float x, float y, float radius );
    Circle( Vector2 pos, float radius );
    virtual ~Circle( void );

    virtual string toString( void ) const;

    Vector2 pos ( void );

    float diameter( void );

    float top   ( void );
    float bottom( void );
    float left  ( void );
    float right ( void );

    bool collides(Circle other);
    bool collides(Rect other);
    bool containsPoint(Vector2 point);

};

#endif