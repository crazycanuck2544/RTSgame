#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Common.h"
#include "GameObject.h"

#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL.h>

class RenderTarget;
class CachedText;

class Texture :
    public GameObject
{

    friend class RenderTarget;
    friend class CachedText;

private:

    string
        _filename;

    GLuint
        _texture;

    Rect
        _size;

    virtual void init( SDL_Surface* pSurface );

    virtual GLuint GLTexture( void ) { return _texture; }

public:

    Texture( void );
    virtual ~Texture( void );

    virtual string toString( void ) const;

    virtual void init( string filename );
    virtual void term( void );

    virtual Rect size( void ) { return _size; }

};

#endif