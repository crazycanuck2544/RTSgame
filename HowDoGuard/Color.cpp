
#include "Color.h"
#include "RenderTarget.h"
#include "CachedText.h"

Color Color::BLACK             = Color(0,      0,   0);
Color Color::WHITE             = Color(255, 255, 255);
Color Color::RED             = Color(255, 0,   0);
Color Color::GREEN             = Color(0,   255, 0);
Color Color::BLUE             = Color(0,   0,   255);
Color Color::CORNFLOWER_BLUE = Color(100, 149, 237);
Color Color::STORM             = Color(0,   170, 170);

Color::Color( float r, float g, float b )
{
    setFrac(r, g, b);
}

Color::Color( float r, float g, float b, float a )
{
    setFrac(r, g, b, a);
}

Color::Color( int r, int g, int b )
{
    setByte(r, g, b);
}

Color::Color( int r, int g, int b, int a )
{
    setByte(r, g, b, a);
}

Color::~Color( void )
{
}

string Color::toString( void ) const
{
    stringstream ss;
    ss << "Color [" << byteR() << ", " << byteG() << ", " << byteB() << ", " << byteA() << "]" << endl;
    return ss.str();
}

void Color::setFrac( float r, float g, float b )
{
    R = (int)(clamp(r, 0.0f, 1.0f) * 255.0f);
    G = (int)(clamp(g, 0.0f, 1.0f) * 255.0f);
    B = (int)(clamp(b, 0.0f, 1.0f) * 255.0f);
    A = 255;
}

void Color::setFrac( float r, float g, float b, float a )
{
    R = (int)(clamp(r, 0.0f, 1.0f) * 255.0f);
    G = (int)(clamp(g, 0.0f, 1.0f) * 255.0f);
    B = (int)(clamp(b, 0.0f, 1.0f) * 255.0f);
    A = (int)(clamp(a, 0.0f, 1.0f) * 255.0f);
}

void Color::setByte( int r, int g, int b )
{
    R = clamp(r, 0, 255);
    G = clamp(g, 0, 255);
    B = clamp(b, 0, 255);
    A = 255;
}

void Color::setByte( int r, int g, int b, int a )
{
    R = clamp(r, 0, 255);
    G = clamp(g, 0, 255);
    B = clamp(b, 0, 255);
    A = clamp(a, 0, 255);
}

SDL_Color Color::SDLColor( void )
{
    SDL_Color color = { R, G, B, A };
    return color;
}
