#pragma once

#ifndef __GAME_INPUT_H__
#define __GAME_INPUT_H__

enum GameInput
{
    INVALID_GAME_INPUT = -1,

    GAME_INPUT_UP,
    GAME_INPUT_DOWN,
    GAME_INPUT_LEFT,
    GAME_INPUT_RIGHT,

    GAME_INPUT_NORTH,
    GAME_INPUT_NORTH_WEST,
    GAME_INPUT_WEST,
    GAME_INPUT_SOUTH_WEST,
    GAME_INPUT_SOUTH,
    GAME_INPUT_SOUTH_EAST,
    GAME_INPUT_EAST,
    GAME_INPUT_NORTH_EAST,

    GAME_INPUT_LIGHT_KICK,
    GAME_INPUT_LIGHT_PUNCH,
    GAME_INPUT_HEAVY_KICK,
    GAME_INPUT_HEAVY_PUNCH,

    GAME_INPUT_GUARD,
    GAME_INPUT_GRAB,

    GAME_INPUT_QCF,
    GAME_INPUT_QCB,
    GAME_INPUT_HCF,
    GAME_INPUT_HCB,
    GAME_INPUT_DRAGON_FIST_FORWARD,
    GAME_INPUT_DRAGON_FIST_BACKWARD,

    GAME_INPUT_ANIMATION_COMPLETE,
    GAME_INPUT_LANDED,
    GAME_INPUT_HIT,

    NUM_GAME_INPUTS
};

const string GAME_INPUT_NAMES[NUM_GAME_INPUTS] =    
{
    "Up",
    "Down",
    "Left",
    "Right",
    
    "North",
    "North-West",
    "West",
    "South-West",
    "South",
    "South-East",
    "East",
    "North-East",
    
    "Light-Kick",
    "Light-Punch",
    "Heavy-Kick",
    "Heavy-Punch",

    "Guard",
    "Grab",
    
    "Quarter-Circle-Forward",
    "Quarter-Circle-Backward",
    "Half-Circle-Forward",
    "Half-Circle-Backward",
    "Dragon-Fist-Forward",
    "Dragon-Fist-Backward",

    "Animation-Complete",
    "Landed",
    "Hit"
};

#endif