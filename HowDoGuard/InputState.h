#pragma once

#ifndef __INPUT_STATE_H__
#define __INPUT_STATE_H__

#include "Common.h"
#include "GameObject.h"

struct InputState 
    : public GameObject
{
    bool 
        Pressed,
        Released,
        Down,
        Hidden;

    int 
        HeldCount;

    InputState( void );
    InputState( bool pressed, bool released, bool down );

    virtual string toString( void ) const;
};

#endif