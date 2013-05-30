#pragma once

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Common.h"
#include "GameObject.h"

#include "Texture.h"

class Sprite :
    public GameObject
{
private:
    
    Texture
        *_pTexture;

public:

    Rect
        SourceRect;

    double
        FrameTime;

    Sprite( void );
    virtual ~Sprite( void );

    virtual string toString( void ) const;

    virtual void init( Texture *pTexture, Rect source, double frameTime );
    virtual void term( void );

    virtual Texture* texture( void ) { return _pTexture; }

};

#endif