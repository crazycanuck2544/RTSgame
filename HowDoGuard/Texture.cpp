#include "Texture.h"
#include "RenderTarget.h"
#include "CachedText.h"

Texture::Texture( void )
{
    _size = Rect::ZERO;
    _filename = "<empty>";
}

Texture::~Texture( void )
{
    term();
}

std::string Texture::toString( void ) const
{
    stringstream ss;
    ss << "Texture [File: " << _filename << "]";
    return ss.str();
}

void Texture::init( string filename )
{
    _filename = filename;

    SDL_Surface *surface = IMG_Load(_filename.c_str());

    if (!surface)
    {
        stringstream ss;
        ss << "Error Loading Image: " << IMG_GetError();
        ERR(toString(), ss.str());
    }

    init(surface);

    SDL_FreeSurface(surface);
}

void Texture::init( SDL_Surface* pSurface )
{
    if (_filename == "")
        _filename = "<generated>";

    if (_texture != OPENGL_INVALID_TEXTURE)
        glDeleteTextures(1, &_texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    _texture = OPENGL_INVALID_TEXTURE;
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    _size = Rect(0.0f, 0.0f, (float)pSurface->w, (float)pSurface->h);

    GLenum mode = GL_RGB;

    if (pSurface->format->BytesPerPixel == 4) 
    {
        mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, 4, (int)_size.Width, (int)_size.Height, 0, mode, GL_UNSIGNED_BYTE, pSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::term( void )
{
    if (_texture != OPENGL_INVALID_TEXTURE)
        glDeleteTextures(1, &_texture);
}