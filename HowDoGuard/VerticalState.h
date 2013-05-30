#pragma once

#ifndef __VERTICAL_STATE_H__
#define __VERTICAL_STATE_H__

enum VerticalState
{
    INVALID_VERTICAL_STATE = -1,

    VERT_STATE_ANY,

    VERT_STATE_GROUND,
    VERT_STATE_DUCKING,
    VERT_STATE_AIR,

    NUM_VERTICAL_STATES
};

const string VERTICAL_STATE_NAMES[NUM_VERTICAL_STATES] =
{
    "Any",

    "Ground",
    "Ducking",
    "Air"
};

#endif