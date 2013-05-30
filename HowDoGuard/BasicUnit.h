#pragma once

#ifndef __BASIC_UNIT_H__
#define __BASIC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Animation.h"
#include "Color.h"
#include "RenderTarget.h"

class BasicUnit :
    public EventDispatcher
{
protected:

    Animation
        *_pAnimation;

    double
        _animationTimeout;

    int
        _frame;

    bool
        _animationComplete;

    virtual void updateAnimation( const FrameData* pFrameData );

public:

    static const EventType
        EVENT_ANIMATION_COMPLETE;

    Vector2
        Pos,
        Origin;

    Size
        Size;

    Color
        BlendColor;

    float
        Rot,
        Depth;

    bool
        Animating,
        Looping;

    BasicUnit( void );
    virtual ~BasicUnit( void );

    virtual string toString( void ) const;

    virtual void init( Animation* pAnimation = nullptr, Vector2 pos = Vector2::ZERO, Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color color = Color::WHITE, float depth = 1.0f);
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void draw  ( const Event& event );

    virtual Animation* animation( void ) { return _pAnimation; }

    virtual void setAnimation( Animation *pAnimation, bool useDefaults = true);

    virtual void animationComplete( const Event& event );

};

#endif