#pragma once

#ifndef __RENDER_TARGET_H__
#define __RENDER_TARGET_H__

#include "Common.h"
#include "GameObject.h"

#include "Color.h"
#include "Font.h"
#include "CachedText.h"
#include "Texture.h"

#include <SDL.h>
#include <SDL_opengl.h>

enum Align
{
    INVALID_ALIGN = -1,
    LEFT,
    CENTER,
    RIGHT,
    NUM_ALIGN
};

class GraphicsSystem;

class RenderTarget :
    public GameObject
{
private: 

    GraphicsSystem
        *_pGraphicsSystem;

    virtual void drawShape( float x, float y, float radius, float shapeValue, Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillShape( float x, float y, float radius, float shapeValue, Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );

public:

    RenderTarget( void );
    virtual ~RenderTarget( void );

    virtual void init( GraphicsSystem *pGraphicsSystem );
    virtual void term( void );

    virtual string toString( void ) const;

    virtual void beginDraw( void );
    virtual void endDraw( void );

    virtual void drawText( Vector2 pos,      string text, Font* pFont,         Color color = Color::WHITE, Align align = Align::INVALID_ALIGN,     float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void drawText( float x, float y, string text, Font* pFont,         Color color = Color::WHITE, Align align = Align::INVALID_ALIGN,     float rotation = 0.0f, Vector2 origin = Vector2::ZERO );

    virtual void drawText( Vector2 pos,      CachedText* pCachedText,         Color color = Color::WHITE, Align align = Align::INVALID_ALIGN,     float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void drawText( float x, float y, CachedText* pCachedText,         Color color = Color::WHITE, Align align = Align::INVALID_ALIGN,     float rotation = 0.0f, Vector2 origin = Vector2::ZERO );

    virtual void draw( Vector2 pos,         Texture *pTexture,                     Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO);
    virtual void draw( float x, float y, Texture *pTexture,                     Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO);
                                                                             
    virtual void draw( Vector2 pos,      Texture *pTexture, Rect sourceRect, Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO);
    virtual void draw( float x, float y, Texture *pTexture, Rect sourceRect, Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO);
                                                                             
    virtual void drawRect( float x, float y, float width, float height,         Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void drawRect( Rect rect,                                         Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void fillRect( float x, float y, float width, float height,         Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillRect( Rect rect,                                         Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawCircle( float x, float y,   float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void drawCircle( Circle circle,                                     Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void fillCircle( float x, float y,   float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillCircle( Circle circle,                                     Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawTriangle( Vector2 pos,      float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillTriangle( Vector2 pos,      float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawTriangle( float x, float y, float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillTriangle( float x, float y, float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawPentagon( Vector2 pos,      float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillPentagon( Vector2 pos,      float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawPentagon( float x, float y, float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillPentagon( float x, float y, float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawHexagon ( Vector2 pos,         float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillHexagon ( Vector2 pos,      float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
                                                                             
    virtual void drawHexagon ( float x, float y, float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );
    virtual void fillHexagon ( float x, float y, float radius,                 Color color = Color::WHITE, float rotation = 0.0f, Vector2 origin = Vector2::ZERO );

};

#endif