#include "InputChange.h"

InputChange::InputChange( void )
{
    Key = SDLK_UNKNOWN;
    Pressed = false;
    Released = false;
}

InputChange::InputChange( SDLKey key )
{
    Key = key;
    Pressed = false;
    Released = false;
}

std::string InputChange::toString( void ) const
{
    return "Input Change";
}

InputChange & InputChange::operator= ( const InputChange &rhs )
{
    if(rhs == *this)
        return *this;

    Pressed = rhs.Pressed;
    Released = rhs.Released;
    Key = rhs.Key;

    return *this;
}

bool  InputChange::operator==( const InputChange &rhs ) const
{
    return (rhs.Pressed == Pressed  && rhs.Released == Released && rhs.Key == Key );
}

bool  InputChange::operator!=( const InputChange &rhs ) const
{
    return !(*this == rhs);
}