#include "BasicUnit.h"

const EventType BasicUnit::EVENT_ANIMATION_COMPLETE = "animationComplete";

BasicUnit::BasicUnit( void )
{
}

BasicUnit::~BasicUnit( void )
{
    term();
}

std::string BasicUnit::toString( void ) const
{
    return "Basic Unit";
}

void BasicUnit::init( Animation* pAnimation /*= nullptr*/, Vector2 pos /*= Vector2::ZERO*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color blendColor /*= Color::WHITE*/, float depth /*= 1.0f*/ )
{
    setAnimation(pAnimation, true);
    Pos = pos;
    Origin = origin;
    Rot = rot;
    BlendColor = blendColor;
    Depth = depth;

    gpEventDispatcher->addEventListener(Event::EVENT_FRAME,     this, &BasicUnit::update);
    gpEventDispatcher->addEventListener(Event::EVENT_RENDER, this, &BasicUnit::draw);
    addEventListener(BasicUnit::EVENT_ANIMATION_COMPLETE,    this, &BasicUnit::animationComplete);
}

void BasicUnit::term( void )
{
    gpEventDispatcher->removeEventListener(Event::EVENT_FRAME,  this, &BasicUnit::update);
    gpEventDispatcher->removeEventListener(Event::EVENT_RENDER, this, &BasicUnit::draw);
    removeEventListener(BasicUnit::EVENT_ANIMATION_COMPLETE,    this, &BasicUnit::animationComplete);
}

void BasicUnit::update( const Event& event )
{
    const FrameData* frameData = event.dataAs<FrameData>();

    if (Animating && !(Looping && _animationComplete))
    {
        updateAnimation(frameData);
    }
}

void BasicUnit::draw( const Event& event )
{
    const RenderData* renderData = event.dataAs<RenderData>();

    if (_pAnimation == nullptr)
        return;

    Sprite *currentFrame = _pAnimation->frame(_frame);

    if (currentFrame == nullptr)
        return;

    renderData->renderTarget()->draw(Pos - Origin, currentFrame->texture(), currentFrame->SourceRect, BlendColor, Rot, Origin);
}

void BasicUnit::setAnimation( Animation *pAnimation, bool useDefaults /*= true*/ )
{
    _pAnimation = pAnimation;

    if (_pAnimation == nullptr)
    {
        Size = Size::ZERO;
        return;
    }

    Size = pAnimation->FrameSize;

    if (useDefaults)
    {
        _frame = 0;
        _animationTimeout = pAnimation->frame(_frame)->FrameTime;

        Animating = pAnimation->Animating;
        Looping = pAnimation->Looping;
        _animationComplete = false;
    }
}

void BasicUnit::updateAnimation( const FrameData* pFrameData )
{
    _animationTimeout -= pFrameData->elapsedMilliseconds();
    if (_animationTimeout < 0)
    {
        if (!Looping)
        {
            if (_frame == _pAnimation->length() - 1)
            {
                _frame = clamp(_frame, 0, _pAnimation->length() - 1);
                dispatchEvent(Event(BasicUnit::EVENT_ANIMATION_COMPLETE));
                return;
            }
        }
        _frame = (_frame + 1) % _pAnimation->length();
        _animationTimeout = _pAnimation->frame(_frame)->FrameTime;
    }
}

void BasicUnit::animationComplete( const Event& event )
{
    _animationComplete = true;
}
