#pragma once

#ifndef __PLAYER_STATE_CHANGE_H__
#define __PLAYER_STATE_CHANGE_H__

#include "Common.h"
#include "GameObject.h"

#include "VerticalState.h"
#include "PlayerState.h"

struct PlayerStateChange
    : GameObject
{

    PlayerState
        OldState,
        NewState;

    VerticalState
        NewVertState;

    PlayerStateChange(PlayerState oldState, PlayerState newState, VerticalState newVert = INVALID_VERTICAL_STATE)
    {
        OldState = oldState;
        NewState = newState;
        NewVertState = newVert;
    }

    virtual string toString( void ) const { return "Player State Change"; }

};

#endif