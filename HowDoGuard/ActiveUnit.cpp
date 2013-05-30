#include "ActiveUnit.h"
#include "InputSystem.h"

ActiveUnit::ActiveUnit( void )
{
}

ActiveUnit::~ActiveUnit( void )
{
    term();
}

std::string ActiveUnit::toString( void ) const
{
    return "Active Unit";
}

void ActiveUnit::init( Animation* pAnimation /*= nullptr*/, Vector2 pos /*= Vector2::ZERO*/, Vector2 vel /*= Vector2::ZERO*/, Vector2 acc /*= Vector2::ZERO*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color color /*= Color::WHITE*/, float depth /*= 1.0f */ )
{
    BasicUnit::init(pAnimation, pos, origin, rot, color, depth);

    Vel = vel;
    Acc = acc;

    gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_PRESSED,  this, &ActiveUnit::inputPressed);
    gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_RELEASED, this, &ActiveUnit::inputReleased);
    gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_HELD,     this, &ActiveUnit::inputHeld);

}

void ActiveUnit::term( void )
{
    BasicUnit::term();

    gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_PRESSED,  this, &ActiveUnit::inputPressed);
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_RELEASED, this, &ActiveUnit::inputReleased);
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_HELD,     this, &ActiveUnit::inputHeld);
}

void ActiveUnit::update( const Event& event )
{
    BasicUnit::update(event);

    const FrameData* frameData = event.dataAs<FrameData>();

    updateMovement(frameData);
}

void ActiveUnit::inputPressed( const Event& event )
{
    //const InputData* inputData = event.dataAs<InputData>();
}

void ActiveUnit::inputReleased( const Event& event )
{
    //const InputData* inputData = event.dataAs<InputData>();
}

void ActiveUnit::inputHeld( const Event& event )
{
    //const InputData* inputData = event.dataAs<InputData>();
}

void ActiveUnit::updateMovement( const FrameData* frameData )
{
    Pos += Vel;
    Vel += Acc;
}
