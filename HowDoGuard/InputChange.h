#pragma once

#ifndef __INPUT_CHANGE_H__
#define __INPUT_CHANGE_H__

#include "Common.h"
#include "GameObject.h"

#include <SDL.h>

struct InputChange
    : GameObject
{
    SDLKey 
        Key;

    bool
        Pressed,
        Released;

    InputChange( void );
    InputChange( SDLKey key );

    virtual string toString( void ) const;

    InputChange &operator= ( const InputChange &rhs );

    bool operator==( const InputChange &rhs ) const;
    bool operator!=( const InputChange &rhs ) const;

};

#endif