#include "Animation.h"

Animation::Animation( void )
{
}

Animation::~Animation( void )
{
    term();
}

std::string Animation::toString( void ) const
{
    return "Animation";
}

void Animation::init( vector<Sprite*> frames, Size size /*= Size::ZERO*/, bool animating /*= false */, bool looping /*= false */ )
{
    _frames = frames;
    FrameSize = size;
    Animating = animating;
    Looping = looping;
}

void Animation::term( void )
{
}

Sprite* Animation::frame( int frame )
{
    if (inBounds(frame, 0, (int)_frames.size()))
    {
        return _frames[frame];
    }

    return nullptr;
}

void Animation::addFrame( Sprite* frame )
{
    _frames.push_back(frame);
}

bool Animation::removeFrame( Sprite* frame )
{
    return vectorRemove(_frames, frame);
}

bool Animation::removeFrame( int frame )
{
    return vectorRemoveAt(_frames, frame);
}