#pragma once

#ifndef __PLAYER_STATE_H__
#define __PLAYER_STATE_H__

enum PlayerState
{
    INVALID_PLAYER_STATE = -1,

    PLAYER_STATE_IDLE,

    PLAYER_STATE_DUCKING_START,
    PLAYER_STATE_DUCKING,

    PLAYER_STATE_JUMPING_START,
    PLAYER_STATE_AIR,

    PLAYER_STATE_WALK,

    PLAYER_STATE_GUARD,
    
    PLAYER_STATE_LIGHT_PUNCH,
    PLAYER_STATE_LIGHT_KICK,
    PLAYER_STATE_HEAVY_PUNCH,
    PLAYER_STATE_HEAVY_KICK,

    PLAYER_STATE_GRAB,
    PLAYER_STATE_GRAB_MISS,
    PLAYER_STATE_LANDING,
    PLAYER_STATE_KNOCKDOWN,
    PLAYER_STATE_RECOVERY,
    PLAYER_STATE_JUGGLE,

    PLAYER_STATE_HIT_STUN,
    PLAYER_STATE_GUARD_STUN,

    NUM_PLAYER_STATES
};

const string PLAYER_STATE_NAMES[NUM_PLAYER_STATES] =
{
    "Idle",

    "Duck-Start",
    "Ducking",

    "Jump-Start",
    "Air",

    "Walk",

    "Guard",

    "Light-Punch",
    "Light-Kick",
    "Heavy-Punch",
    "Heavy-Kick",
    
    "Grab",
    "Grab-Miss",
    "Landing",
    "Knockdown",
    "Recovery",
    "Juggle",

    "Hit-Stun",
    "Guard-Stun"
};

#endif