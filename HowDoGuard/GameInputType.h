#pragma once

#ifndef __GAME_INPUT_TYPE_H__
#define __GAME_INPUT_TYPE_H__

enum GameInputType
{
    INVALID_GAME_INPUT_TYPE = -1,

    GAME_INPUT_TYPE_PRESSED,
    GAME_INPUT_TYPE_RELEASED,
    GAME_INPUT_TYPE_HELD,
    GAME_INPUT_TYPE_OTHER,

    NUM_GAME_INPUT_TYPES
};

const string GAME_INPUT_TYPE_NAMES[NUM_GAME_INPUT_TYPES] = 
{
    "Pressed",
    "Released",
    "Held",
    "Other"
};

#endif