#include "Player.h"
#include "Game.h"

Player::Player( void )
{
}

Player::~Player( void )
{
    term();
}

std::string Player::toString( void ) const
{
    return "Player";
}

void Player::init( PlayerIndex index, PlayerType type, Vector2 pos /*= Vector2::ZERO*/, Color color /*= Color::WHITE*/, float depth /*= 1.0f */ )
{
    ActiveUnit::init(nullptr, pos, Vector2::ZERO, Vector2::ZERO, Vector2::ZERO, 0.0f, color, depth);

    _playerIndex = index;
    _playerType = type;

    setAnimationKeys();

    switchState(PLAYER_STATE_AIR, VERT_STATE_AIR);

    _gravity     = -gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("gravity")));
    _ground      =  420.0f;
    _maxSpeed    =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("maxSpeed")));
    _jumpVelInit =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("jumpVelStart")));
    _jumpVelMax  =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("jumpVelMax")));
    _jumpVelLeft =  _jumpVelMax;
    _damping     =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("damping")));
    _airDamping  =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("airDamping")));
    _terminalVel =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("terminalVel")));
    _movementAcc =  gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("movementAcc")));

    _stateData = &gpDataManager->PlayerStateData[_playerType];
}

void Player::term( void )
{
    ActiveUnit::term();
}

void Player::update( const Event& event )
{
    ActiveUnit::update(event);

    //cout << PLAYER_STATE_NAMES[_state] << endl;
    //INF(toString(), Vel.toString());

    if (_vertState == VERT_STATE_AIR)
    {
        Vel.Y -= _gravity;
        if (Vel.Y > _terminalVel)
            Vel.Y = _terminalVel;

        if (_state == PLAYER_STATE_AIR)
        {
            if (sign(Vel.Y) == 1)
            {
                setAnimation(gpDataManager->pAnimations->get(_playerType + "-descending"));
            }
            else
            {
                setAnimation(gpDataManager->pAnimations->get(_playerType + "-ascending"));
            }
        }

        if (Pos.Y > _ground) //TODO: Replace with ground checking
        {
            Vel.Y = 0;
            Pos.Y = _ground;
            checkStateData(GAME_INPUT_LANDED);
        }
    }

    if (abs(Vel.X) < 0.01)
        Vel.X = 0.0f;

    if (Vel.X != 0.0f)
    {
        float damp;

        if (_vertState == VERT_STATE_GROUND || _vertState == VERT_STATE_DUCKING)
            damp = _damping;
        else
            damp = _airDamping;

        Vel.X -= damp * sign(Vel.X);
    }
}

void Player::inputPressed( const Event& event )
{
    ActiveUnit::inputPressed(event);

    const InputData* inputData = event.dataAs<InputData>();

    if (inputData->Index != _playerIndex)
        return;

    checkStateData(inputData->Input, GAME_INPUT_TYPE_PRESSED);
}

void Player::inputReleased( const Event& event )
{
    ActiveUnit::inputReleased(event);

    const InputData* inputData = event.dataAs<InputData>();

    if (inputData->Index != _playerIndex)
        return;

    checkStateData(inputData->Input, GAME_INPUT_TYPE_RELEASED);
}

void Player::inputHeld( const Event& event )
{
    ActiveUnit::inputHeld(event);

    const InputData* inputData = event.dataAs<InputData>();

    if (inputData->Index != _playerIndex)
        return;
    
    checkStateData(inputData->Input, GAME_INPUT_TYPE_HELD);

    if (inputData->Input == GAME_INPUT_UP && _state == PLAYER_STATE_AIR)
    {
        if (_jumpVelLeft > 0.0f)
        {
            Vel.Y -= 1.0f;
            _jumpVelLeft -= 1.0f;
        }
    }

    if (_state == PLAYER_STATE_WALK || _state == PLAYER_STATE_AIR)
    {
        if (inputData->Input == GAME_INPUT_LEFT)
        {
            Vel.X -= _movementAcc;
        }
        else if (inputData->Input == GAME_INPUT_RIGHT)
        {
            Vel.X += _movementAcc;
        }
        if (abs(Vel.X) > _maxSpeed)
            Vel.X = _maxSpeed * sign(Vel.X);
    }
}

void Player::animationComplete( const Event& event )
{
    ActiveUnit::animationComplete(event);

    if (_state == PLAYER_STATE_JUMPING_START)
    {
        Vel.Y -= _jumpVelInit;
        _jumpVelLeft = _jumpVelMax - _jumpVelInit;
    }

    checkStateData(GAME_INPUT_ANIMATION_COMPLETE);
}

void Player::setAnimationKeys( void )
{
    addAnimationKey(PLAYER_STATE_IDLE,          _playerType + "-idle",               VERT_STATE_GROUND);
                                                                                     
    addAnimationKey(PLAYER_STATE_DUCKING_START, _playerType + "-duck-start",         VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_DUCKING,       _playerType + "-ducking",            VERT_STATE_DUCKING);
                                                                                     
    addAnimationKey(PLAYER_STATE_JUMPING_START, _playerType + "-jump-start",         VERT_STATE_GROUND);
                                                                                     
    addAnimationKey(PLAYER_STATE_WALK,          _playerType + "-walk",               VERT_STATE_GROUND);
                                                                                     
    addAnimationKey(PLAYER_STATE_GUARD,         _playerType + "-guard",              VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_GUARD,         _playerType + "-duck-guard",         VERT_STATE_DUCKING);
    addAnimationKey(PLAYER_STATE_GUARD,         _playerType + "-air-guard",          VERT_STATE_AIR);
                                                                                     
    addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,   _playerType + "-glp",                VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_LIGHT_KICK,    _playerType + "-glk",                VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,   _playerType + "-ghp",                VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_HEAVY_KICK,    _playerType + "-ghk",                VERT_STATE_GROUND);
                                                                                     
    addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,   _playerType + "-dlp",                VERT_STATE_DUCKING);
    addAnimationKey(PLAYER_STATE_LIGHT_KICK,    _playerType + "-dlk",                VERT_STATE_DUCKING);
    addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,   _playerType + "-dhp",                VERT_STATE_DUCKING);
    addAnimationKey(PLAYER_STATE_HEAVY_KICK,    _playerType + "-dhk",                VERT_STATE_DUCKING);
                                                                                     
    addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,   _playerType + "-alp",                VERT_STATE_AIR);
    addAnimationKey(PLAYER_STATE_LIGHT_KICK,    _playerType + "-alk",                VERT_STATE_AIR);
    addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,   _playerType + "-ahp",                VERT_STATE_AIR);
    addAnimationKey(PLAYER_STATE_HEAVY_KICK,    _playerType + "-ahk",                VERT_STATE_AIR);
                                                                                     
    addAnimationKey(PLAYER_STATE_GRAB,          _playerType + "-grab",               VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_GRAB_MISS,     _playerType + "-grab-miss",          VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_LANDING,       _playerType + "-landing",            VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_KNOCKDOWN,     _playerType + "-knockdown",          VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_RECOVERY,      _playerType + "-recovery",           VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_JUGGLE,        _playerType + "-juggle",             VERT_STATE_AIR);
                                                                                     
    addAnimationKey(PLAYER_STATE_HIT_STUN,      _playerType + "-hit-stun",           VERT_STATE_GROUND);
    addAnimationKey(PLAYER_STATE_GUARD_STUN,    _playerType + "-guard-stun",         VERT_STATE_GROUND);

    addAnimationKey(PLAYER_STATE_HIT_STUN,      _playerType + "-ducking-hit-stun",   VERT_STATE_DUCKING);
    addAnimationKey(PLAYER_STATE_GUARD_STUN,    _playerType + "-ducking-guard-stun", VERT_STATE_DUCKING);

    addAnimationKey(PLAYER_STATE_GUARD_STUN,    _playerType + "-air-guard-stun",     VERT_STATE_AIR);
}

void Player::addAnimationKey( PlayerState state, ItemKey key, VerticalState vertState /*= VERT_STATE_ANY */ )
{
    _animKeys.insert(pair<StatePair, ItemKey>(StatePair(vertState, state), key));
}

void Player::switchState( PlayerState state /*= INVALID_PLAYER_STATE*/, VerticalState vertState /*= INVALID_VERTICAL_STATE */ )
{
    if (_state == state && _vertState == vertState)
        return;

    if (_state != INVALID_PLAYER_STATE)
        _state = state;

    Game::stateText->setText(PLAYER_STATE_NAMES[_state]);

    if (_vertState != INVALID_VERTICAL_STATE)
        _vertState = vertState;

    StatePair statePair(vertState, state);

    if (mapContainsKey(_animKeys, statePair))
    {
        if (!gpDataManager->pAnimations->contains(_animKeys[statePair]))
            return;

        setAnimation(gpDataManager->pAnimations->get(_animKeys[statePair]));
    }
}

void Player::checkStateData( GameInput input, GameInputType type /*= GAME_INPUT_TYPE_OTHER*/ )
{
    pair<GameInput, GameInputType> typePair(input, type);

    if (mapContainsKey(*_stateData, typePair))
    {
        if (mapContainsKey((*_stateData)[typePair], _vertState))
        {
            PlayerStateChangeList list = (*_stateData)[typePair][_vertState];

            for (unsigned int i = 0; i < list.size(); ++i)
            {
                if (list[i].OldState == _state)
                {
                    switchState(list[i].NewState, list[i].NewVertState);
                }
            }
        }
    }
}

void Player::setAnimation( Animation *pAnimation, bool useDefaults /*= true */ )
{
    ActiveUnit::setAnimation(pAnimation, useDefaults);

    Origin = Vector2(Size.X / 2.0f, Size.Y);
}
