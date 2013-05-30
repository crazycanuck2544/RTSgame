#pragma once

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Event.h"

#include "InputChange.h"
#include "InputState.h"
#include "InputPress.h"
#include "GameInput.h"
#include "PlayerIndex.h"

#include <SDL.h>

#include <queue>

#define INPUT_BUFFER_MAX 15

typedef pair<GameInput, InputState> InputPair;

class InputSystem :
    public EventDispatcher
{
private:

    map<PlayerIndex, map<GameInput, InputState>>
        _inputStates;

    queue<InputChange>
        _inputChanges;

    vector<GameInput>
        _inputBufferIgnore,
        _eightWayDir;

    map<PlayerIndex, vector<InputPress>>
        _inputBuffer;

    map<PlayerIndex, map<SDLKey, GameInput>>
        _alias;

    map<PlayerIndex, map<SDLKey, bool>>
        _keyStates;

    map<GameInput, vector<GameInput>>
        _simultanious,
        _consecutive;

    map<GameInput, GameInput>
        _exclusive;

    vector<SDL_Joystick*>
        _joysticks;

    unsigned int
        _maxPlayers;

    Uint8
        *_sdlKeys;

    virtual void process( const FrameData* frameData );

    virtual void addExclusive( const GameInput first, const GameInput second );

    void press  ( const GameInput input, const PlayerIndex index );
    void release( const GameInput input, const PlayerIndex index );

    InputState * getInputState( GameInput input, const PlayerIndex index );
    void addInputToBuffer( GameInput input, const PlayerIndex index );

public:

    static const EventType 
        EVENT_INPUT_PRESSED,
        EVENT_INPUT_RELEASED,
        EVENT_INPUT_HELD;

    InputSystem( void );
    virtual ~InputSystem( void );

    virtual void init ( void );
    virtual void term ( void );

    virtual string toString( void ) const;

    virtual void update( const Event& event );
};

#endif