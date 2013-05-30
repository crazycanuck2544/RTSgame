#include "RenderTarget.h"
#include "GraphicsSystem.h"

RenderTarget::RenderTarget( void )
{
}

RenderTarget::~RenderTarget( void )
{
    term();
}

void RenderTarget::init( GraphicsSystem *pGraphicsSystem )
{
    _pGraphicsSystem = pGraphicsSystem;
}

void RenderTarget::term( void )
{
}

std::string RenderTarget::toString( void ) const
{
    return "Render Target";
}

void RenderTarget::beginDraw( void )
{
    Color clearColor = _pGraphicsSystem->clearColor();

    glClearColor(clearColor.fracR(), clearColor.fracG(), clearColor.fracB(), clearColor.fracA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
}

void RenderTarget::endDraw( void )
{
    SDL_GL_SwapBuffers();
}

// ShapeValue 1.5 - Draws Triangle
// ShapeValue 2   - Draws Square
// ShapeValue 3   - Draws Hexagon
// ShapeValue 4   - Draws Octagon
// ShapeValue 5   - Draws Decagon
// ShapeValue 6   - Draws Circle
// ShapeValue 12  - Draws Better Circle
void RenderTarget::drawShape( float x, float y, float radius, float shapeValue, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBegin(GL_LINE_LOOP);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex3f(cosf(i) * radius, sinf(i) * radius, 0.0f);
    }

    glEnd();

    glPopMatrix();
}

void RenderTarget::fillShape( float x, float y, float radius, float shapeValue, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBegin(GL_POLYGON);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex3f(cosf(i) * radius, sinf(i) * radius, 0.0f);
    }

    glEnd();

    glPopMatrix();
}

void RenderTarget::drawText( Vector2 pos, string text, Font* pFont, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawText(pos.X, pos.Y, text, pFont, color, align, rotation, origin);
}

void RenderTarget::drawText( float x, float y, string text, Font* pFont, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    CachedText cachedText;
    cachedText.init(text, pFont);

    drawText(x, y, &cachedText, color, align, rotation, origin);
}

void RenderTarget::drawText( Vector2 pos, CachedText* pCachedText, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawText(pos.X, pos.Y, pCachedText, color, align, rotation, origin);
}

void RenderTarget::drawText( float x, float y, CachedText* pCachedText, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    if (pCachedText->text().length() == 0)
        return;

    if (pCachedText->texture() == nullptr)
    {
        ERR(toString(), "Invalid Cached Text");
        return;
    }

    switch (align)
    {
    case LEFT:

        origin.X = 0;

        break;
    case CENTER:

        origin.X = pCachedText->texture()->size().halfWidth();

        break;
    case RIGHT:

        origin.X = pCachedText->texture()->size().Width;

        break;
    }

    if (align != INVALID_ALIGN)
        x -= origin.X;

    draw(x, y, pCachedText->texture(), color, rotation, origin);
}

void RenderTarget::draw( Vector2 pos, Texture *pTexture, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    draw(pos.X, pos.Y, pTexture, color, rotation, origin);
}

void RenderTarget::draw( float x, float y, Texture *pTexture, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    draw(x, y, pTexture, pTexture->size(), color, rotation, origin);
}

void RenderTarget::draw( Vector2 pos, Texture *pTexture, Rect sourceRect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    draw(pos.X, pos.Y, pTexture, sourceRect, color, rotation, origin);
}

void RenderTarget::draw( float x, float y, Texture *pTexture, Rect sourceRect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation), 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBindTexture(GL_TEXTURE_2D, pTexture->GLTexture());

    glBegin(GL_QUADS);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    Rect texSize = pTexture->size();
    Rect convSrcRect = Rect(sourceRect.left() / texSize.Width, sourceRect.top() / texSize.Height, sourceRect.Width / texSize.Width, sourceRect.Height / texSize.Height);

    glTexCoord2d(convSrcRect.left(),    convSrcRect.top());        glVertex2d(0.0,                    0.0);
    glTexCoord2d(convSrcRect.right(),    convSrcRect.top());        glVertex2d(sourceRect.Width,    0.0);
    glTexCoord2d(convSrcRect.right(),    convSrcRect.bottom());    glVertex2d(sourceRect.Width,    sourceRect.Height);
    glTexCoord2d(convSrcRect.left(),    convSrcRect.bottom());    glVertex2d(0.0,                    sourceRect.Height);

    glEnd();

    glPopMatrix();
}

void RenderTarget::drawRect( float x, float y, float width, float height, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Rect rect = Rect(x, y, width, height);
    drawRect(rect, color, rotation, origin);
}

void RenderTarget::drawRect( Rect rect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(rect.X, rect.Y, 0);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBegin(GL_LINE_LOOP); 

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glVertex3f(0.0f,       0.0f,        0.0f);
    glVertex3f(rect.Width, 0.0f,        0.0f);
    glVertex3f(rect.Width, rect.Height, 0.0f);
    glVertex3f(0.0f,       rect.Height, 0.0f);

    glEnd(); 

    glPopMatrix();
}

void RenderTarget::fillRect( float x, float y, float width, float height, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Rect rect = Rect(x, y, width, height);
    fillRect(rect, color, rotation, origin);
}

void RenderTarget::fillRect( Rect rect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(rect.X, rect.Y, 0);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBegin(GL_QUADS);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glVertex3f(0.0f,       0.0f,        0.0f);
    glVertex3f(rect.Width, 0.0f,        0.0f);
    glVertex3f(rect.Width, rect.Height, 0.0f);
    glVertex3f(0.0f,       rect.Height, 0.0f);

    glEnd();

    glPopMatrix();
}

void RenderTarget::drawCircle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Circle circle = Circle(x, y, radius);
    drawCircle(circle, color, rotation, origin);
}

void RenderTarget::drawCircle( Circle circle, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(circle.X, circle.Y, circle.Radius, 12, color, rotation, origin);
}

void RenderTarget::fillCircle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Circle circle = Circle(x, y, radius);
    fillCircle(circle, color, rotation, origin);
}

void RenderTarget::fillCircle( Circle circle, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(circle.X, circle.Y, circle.Radius, 12, color, rotation, origin);
}

void RenderTarget::drawTriangle( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawTriangle(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::fillTriangle( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillTriangle(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::drawTriangle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(x, y, radius, 1.5, color, rotation, origin);
}

void RenderTarget::fillTriangle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(x, y, radius, 1.5, color, rotation, origin);
}

void RenderTarget::drawPentagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawPentagon(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::fillPentagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillPentagon(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::drawPentagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(x, y, radius, 2.5, color, rotation, origin);
}

void RenderTarget::fillPentagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(x, y, radius, 2.5, color, rotation, origin);
}

void RenderTarget::drawHexagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(pos.X, pos.Y, radius, 3, color, rotation, origin);
}

void RenderTarget::fillHexagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(pos.X, pos.Y, radius, 3, color, rotation, origin);
}

void RenderTarget::drawHexagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(x, y, radius, 3, color, rotation, origin);
}

void RenderTarget::fillHexagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(x, y, radius, 3, color, rotation, origin);
}