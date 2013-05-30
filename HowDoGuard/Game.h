#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "Common.h"
#include "EventDispatcher.h"
#include "Event.h"

#include "DataManager.h"

#include "GraphicsSystem.h"
#include "RenderTarget.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include "CachedText.h"

#include "BasicUnit.h"

#include "InputSystem.h"

#include "Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

#include "Toast.h"
#include "Player.h"

class Game :
    public EventDispatcher
{
private:

    GraphicsSystem
        *_pGraphicsSystem;

    InputSystem 
        *_pInputSystem;

    bool
        _running;

    float 
        _targetFPS,
        _currentFPS;

public:

    //TODO: Remove
    static bool endNow;
    Toast *toast;
    Player *test, *test2;
    BasicUnit *bg;
    Font *fpsFont;
    static CachedText *fpsText, *stateText;

    Game( void );
    virtual ~Game( void );

    virtual string toString( void ) const;

    void init( void );
    void term( void );

    void start( void );
    void stop ( const Event& event );

    void update( const FrameData& frameData );
    void draw  ( const RenderData& renderData );
};

#endif
