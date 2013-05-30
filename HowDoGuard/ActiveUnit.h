#pragma once

#ifndef __ACTIVE_UNIT_H__
#define __ACTIVE_UNIT_H__

#include "Common.h"
#include "BasicUnit.h"

class ActiveUnit :
    public BasicUnit
{
protected:

    virtual void updateMovement( const FrameData* frameData );

public:

    Vector2
        Vel,
        Acc;

    ActiveUnit( void );
    virtual ~ActiveUnit( void );

    virtual string toString( void ) const;

    virtual void init( Animation* pAnimation = nullptr, Vector2 pos = Vector2::ZERO, Vector2 vel = Vector2::ZERO, Vector2 acc = Vector2::ZERO, Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color color = Color::WHITE, float depth = 1.0f );
    virtual void term( void );

    virtual void update( const Event& event );

    virtual void inputPressed ( const Event& event );
    virtual void inputReleased( const Event& event );
    virtual void inputHeld    ( const Event& event );

};

#endif