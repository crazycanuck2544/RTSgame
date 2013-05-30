#include "Sprite.h"

Sprite::Sprite( void )
{
    _pTexture = nullptr;
}

Sprite::~Sprite( void )
{
    term();
}

string Sprite::toString( void ) const
{
    return "Sprite";
}

void Sprite::init( Texture *pTexture, Rect source, double frameTime )
{
    SourceRect = source;
    _pTexture = pTexture;
    FrameTime = frameTime;
}

void Sprite::term( void )
{
}
