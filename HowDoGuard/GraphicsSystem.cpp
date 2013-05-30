#include "GraphicsSystem.h"


GraphicsSystem::GraphicsSystem( void )
{
    _clearColor = Color::STORM;
}


GraphicsSystem::~GraphicsSystem( void )
{
    term();
}

void GraphicsSystem::init( void )
{
    INF(toString(), "Initializing");

    //TODO: Move these
    int width = 1143, height = 480;
    string title = "Testing";

    _clearColor = Color::STORM;
    int screenBPP = 32;

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        ERR(toString(), "Failed to initialize SDL");
        die();
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,            16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,            32);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,    1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,        1);

    if (SDL_SetVideoMode(width, height, screenBPP, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL) == nullptr)
    {
        ERR(toString(), "Failed to create SDL window");
        die();
    }

    SDL_WM_SetCaption(title.c_str(), nullptr);

    initGL(width, height);

    _pRenderTarget = New RenderTarget();
    _pRenderTarget->init(this);

    if (TTF_Init() < 0)
    {
        ERR(toString(), "Failed to initialize TTF Addon");
        die();
    }

    INF(toString(), "Complete");
}

void GraphicsSystem::term( void )
{
    delete _pRenderTarget;

    TTF_Quit();
    SDL_Quit();
}

std::string GraphicsSystem::toString( void ) const
{
    return "Graphics System";
}

void GraphicsSystem::initGL( int width, int height )
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(_clearColor.fracR(), _clearColor.fracG(), _clearColor.fracB(), _clearColor.fracA());
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        stringstream ss;
        ss << "Failed to initialize OpenGL (" << gluErrorString(error) << ")";

        ERR(toString(), ss.str());
        die();
    }
}

RenderTarget * GraphicsSystem::renderTarget( void )
{
    return _pRenderTarget;
}

Color GraphicsSystem::clearColor( void )
{
    return _clearColor;
}
