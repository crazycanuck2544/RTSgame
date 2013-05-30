#pragma once

#ifndef __GRAPHICS_SYSTEM_H__
#define __GRAPHICS_SYSTEM_H__

#include "Common.h"
#include "GameObject.h"

#include "RenderTarget.h"
#include "Color.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_mixer.lib")
#pragma comment(lib, "SDL_ttf.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

class GraphicsSystem :
    public GameObject
{
private:

    Color
        _clearColor;

    RenderTarget
        *_pRenderTarget;
    
    void initGL( int width, int height );

public:

    GraphicsSystem( void );
    virtual ~GraphicsSystem( void );

    virtual void init( void );
    virtual void term( void );

    virtual string toString( void ) const;

    virtual RenderTarget *renderTarget( void );
    virtual Color clearColor( void );

};

#endif