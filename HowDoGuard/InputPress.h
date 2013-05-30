#pragma once

#ifndef __INPUT_PRESS_H__
#define __INPUT_PRESS_H__

#include "Common.h"
#include "GameObject.h"

#include "GameInput.h"

struct InputPress
    : GameObject
{
    GameInput
        Input;

    time_t
        Time;

    InputPress( void )
    {
        Input = INVALID_GAME_INPUT;
        Time = now();
    }

    InputPress( GameInput input )
    {
        Input = input;
        Time = now();
    }

    virtual string toString( void ) const 
    { 
        return "Input Press";
    }
};

#endif