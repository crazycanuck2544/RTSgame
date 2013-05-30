#pragma once

#ifndef __FONT_H__
#define __FONT_H__

#include "Common.h"
#include "GameObject.h"

#include <SDL_ttf.h>

class RenderTarget;
class CachedText;

class Font :
    public GameObject
{

    friend class RenderTarget;
    friend class CachedText;

private:

    string
        _filename;

    TTF_Font
        *_pFont;

    int
        _size;

    virtual TTF_Font* SDLFont( void ) { return _pFont; }

public:

    Font( string filename, int size );
    virtual ~Font( void );

    virtual string toString( void ) const;

    virtual int size( void ) { return _size; }

};

#endif