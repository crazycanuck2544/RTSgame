#include "InputState.h"

InputState::InputState( void )
{
    Pressed = false;
    Released = true;
    Down = false;
    Hidden = false;
    HeldCount = 0;
}

InputState::InputState( bool pressed, bool released, bool down )
{
    Pressed = pressed;
    Released = released;
    Down = down;
    Hidden = false;
    HeldCount = 0;
}

string InputState::toString( void ) const
{
    return "Input State";
}