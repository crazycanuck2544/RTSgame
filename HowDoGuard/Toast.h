#pragma once

#ifndef __TOAST_H__
#define __TOAST_H__

#include "Common.h"
#include "BasicUnit.h"

#include "DataManager.h"

#include "PlayerState.h"

class Toast :
    public BasicUnit
{
private:

    Vector2
        _vel;

    Vector2
        _acc,
        _gravity;

    PlayerState
        _state;

    bool 
        _inAir;

    Rect
        _size;

    float 
        _ground;

    vector<PlayerState>
        _validWalkStates,
        _validJumpStates;

public:

    Toast( void );
    virtual ~Toast( void );

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );

    virtual void inputPressed ( const Event& event );
    virtual void inputReleased( const Event& event );
    virtual void inputHeld    ( const Event& event );

    virtual void jump( void );
    
    virtual Rect bounds( void );

    virtual void setState( PlayerState newState );

    virtual void animationComplete( const Event& event );

};

#endif