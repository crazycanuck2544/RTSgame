
#pragma once

#ifndef __COLOR_H__
#define __COLOR_H__

#include "Common.h"
#include "GameObject.h"

#include <SDL.h>

class Color
    : public GameObject
{

    friend class RenderTarget;
    friend class CachedText;

private:

    virtual SDL_Color SDLColor( void );

public:

    int 
        R,
        G,
        B,
        A;

    static Color
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE,
        CORNFLOWER_BLUE,
        STORM;

    Color( void ) { setByte(0, 0, 0, 0); }

    Color( float r, float g, float b );
    Color( float r, float g, float b, float a );

    Color( int r, int g, int b );
    Color( int r, int g, int b, int a );

    virtual ~Color( void );

    virtual string toString( void ) const;

    float fracR( void ) const { return (float)(R * 255.0f); }
    float fracG( void ) const { return (float)(G * 255.0f); }
    float fracB( void ) const { return (float)(B * 255.0f); }
    float fracA( void ) const { return (float)(A * 255.0f); }

    int byteR( void ) const { return R; }
    int byteG( void ) const { return G; }
    int byteB( void ) const { return B; }
    int byteA( void ) const { return A; }

    void setFrac( float r, float g, float b );
    void setFrac( float r, float g, float b, float a );

    void setByte( int r, int g, int b );
    void setByte( int r, int g, int b, int a );

};

#endif  //__COLOR_H__