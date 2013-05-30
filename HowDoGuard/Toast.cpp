#include "Toast.h"
#include "InputSystem.h"

Toast::Toast( void )
{
}

Toast::~Toast (void )
{
    term();
}

std::string Toast::toString( void ) const
{
    return "Toast";
}

void Toast::init( void )
{
    BasicUnit::init(gpDataManager->pAnimations->get("toast-idle"), Vector2(300, 165));

    _vel = Vector2::ZERO;
    _acc = Vector2::ZERO;
    _gravity = Vector2(0, 1);

    _inAir = false;
    _ground = 420;

    _size = Rect(0, 0, 255, 255);

    gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_PRESSED,  this, &Toast::inputPressed);
    gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_RELEASED, this, &Toast::inputReleased);
    gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_HELD,     this, &Toast::inputHeld);

    _validWalkStates = makeVector(5, PLAYER_STATE_IDLE, PLAYER_STATE_DUCKING_START, PLAYER_STATE_LANDING, PLAYER_STATE_WALK);
    _validJumpStates = makeVector(6, PLAYER_STATE_IDLE, PLAYER_STATE_DUCKING_START, PLAYER_STATE_DUCKING, PLAYER_STATE_LANDING, PLAYER_STATE_WALK);
}

void Toast::term( void )
{
    BasicUnit::term();

    gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_PRESSED,  this, &Toast::inputPressed);
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_RELEASED, this, &Toast::inputReleased);
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_HELD,     this, &Toast::inputHeld);
}

void Toast::update( const Event& event )
{
    BasicUnit::update(event);

    Pos += _vel;
    _vel += _acc;

    if (_inAir)
        _vel += _gravity;

    if (_inAir && bounds().bottom() > _ground)
    {
        _inAir = false;
        Pos.Y = _ground - _size.Height;
        _vel.X = _vel.Y = 0;

        setState(PLAYER_STATE_IDLE);
    }
}

void Toast::inputPressed( const Event& event )
{
    const InputData* inputData = event.dataAs<InputData>();

    cout << GAME_INPUT_NAMES[inputData->Input] << endl;

    switch (inputData->Input)
    {
    case GAME_INPUT_NORTH:

        jump();

        break;
    case GAME_INPUT_NORTH_WEST:

        jump();
        _vel.X = -2;

        break;
    case GAME_INPUT_NORTH_EAST:

        jump();
        _vel.X = 2;

        break;
    case GAME_INPUT_HEAVY_KICK:

        if (!_inAir)
        {
            setState(PLAYER_STATE_HEAVY_PUNCH);
        }

        break;
    }
}

void Toast::inputReleased( const Event& event )
{
    const InputData* inputData = event.dataAs<InputData>();

    switch (inputData->Input)
    {
    case GAME_INPUT_WEST:
    case GAME_INPUT_EAST:

        if (!_inAir && _state != PLAYER_STATE_HEAVY_PUNCH)
        {
            setState(PLAYER_STATE_IDLE);
            _vel.X = 0;
        }

        break;
    }
}

void Toast::inputHeld( const Event& event )
{
    const InputData* inputData = event.dataAs<InputData>();

    switch (inputData->Input)
    {
    case GAME_INPUT_WEST:

        if (!_inAir && vectorContains(_validWalkStates, _state))
        {
            setState(PLAYER_STATE_WALK);
            _vel.X = -2;
        }

        break;
    case GAME_INPUT_EAST:

        if (!_inAir && vectorContains(_validWalkStates, _state))
        {
            setState(PLAYER_STATE_WALK);
            _vel.X = 2;
        }

        break;
    }
}

void Toast::jump( void )
{
    if (_inAir || !vectorContains(_validJumpStates, _state))
        return;

    _inAir = true;
    _vel.Y = -15;
}

Rect Toast::bounds( void )
{
    return Rect(Pos.X, Pos.Y, _size.Width, _size.Height);
}

void Toast::setState( PlayerState newState )
{
    if (_state == newState)
        return;

    _state = newState;

    switch (_state)
    {
    case PLAYER_STATE_IDLE:

        setAnimation(gpDataManager->pAnimations->get("toast-idle"));
        _vel.X = 0;

        break;
    case PLAYER_STATE_WALK:

        setAnimation(gpDataManager->pAnimations->get("toast-walking"));

        break;
    case PLAYER_STATE_HEAVY_PUNCH:

        setAnimation(gpDataManager->pAnimations->get("toast-ghp"));
        _vel.X = 0;

        break;
    }
}

void Toast::animationComplete( const Event& event )
{
    BasicUnit::animationComplete(event);

    if (_state == PLAYER_STATE_HEAVY_PUNCH)
        setState(PLAYER_STATE_IDLE);
}
