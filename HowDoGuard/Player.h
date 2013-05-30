#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Common.h"
#include "ActiveUnit.h"

#include "VerticalState.h"
#include "PlayerState.h"
#include "PlayerStateChange.h"

#include "DataManager.h"

typedef pair<VerticalState, PlayerState> StatePair;
typedef string PlayerType;

class Player :
    public ActiveUnit
{
protected:

    map<StatePair, ItemKey>
        _animKeys;

    PlayerStateMap
        *_stateData;

    PlayerState
        _state;

    VerticalState
        _vertState;

    PlayerIndex 
        _playerIndex;

    PlayerType
        _playerType;

    float
        _gravity,
        _ground,
        _maxSpeed,
        _jumpVelInit,
        _jumpVelMax,
        _jumpVelLeft,
        _damping,
        _terminalVel,
        _airDamping,
        _movementAcc;

    virtual void setAnimationKeys( void );
    virtual void addAnimationKey( PlayerState state, ItemKey key, VerticalState vertState = VERT_STATE_ANY );

    virtual void checkStateData( GameInput input, GameInputType type = GAME_INPUT_TYPE_OTHER );

public:

    Player( void );
    virtual ~Player( void );

    virtual string toString( void ) const;

    virtual void init( PlayerIndex index, PlayerType playerType, Vector2 pos = Vector2::ZERO, Color color = Color::WHITE, float depth = 1.0f );
    virtual void term( void );

    virtual void update( const Event& event );

    virtual void inputPressed ( const Event& event );
    virtual void inputReleased( const Event& event );
    virtual void inputHeld    ( const Event& event );

    virtual void animationComplete( const Event& event );

    virtual void switchState( PlayerState state = INVALID_PLAYER_STATE, VerticalState vertState = INVALID_VERTICAL_STATE );

    virtual void setAnimation( Animation *pAnimation, bool useDefaults = true );

};

#endif