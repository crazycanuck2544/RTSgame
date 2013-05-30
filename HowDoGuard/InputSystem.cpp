#include "InputSystem.h"
#include "Game.h"

const EventType InputSystem::EVENT_INPUT_PRESSED  = "inputPressed";
const EventType InputSystem::EVENT_INPUT_RELEASED = "inputReleased";
const EventType InputSystem::EVENT_INPUT_HELD     = "inputHeld";

InputSystem::InputSystem( void )
{
}

InputSystem::~InputSystem( void )
{
    term();
}

void InputSystem::init( void )
{
    INF(toString(), "Starting Init");

    gpEventDispatcher->addEventListener(Event::EVENT_ENTER_FRAME, this, &InputSystem::update);

    _maxPlayers = 2;

    for (unsigned int index = 0; index < _maxPlayers; ++index)
    {
        PlayerIndex playerIndex = (PlayerIndex)index;
        _alias.insert(pair<PlayerIndex, map<SDLKey, GameInput>>(playerIndex, map<SDLKey, GameInput>()));
    }

    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_w, GAME_INPUT_UP));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_a, GAME_INPUT_LEFT));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_s, GAME_INPUT_DOWN));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_d, GAME_INPUT_RIGHT));

    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_o, GAME_INPUT_LIGHT_PUNCH));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_k, GAME_INPUT_LIGHT_KICK));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_p, GAME_INPUT_HEAVY_PUNCH));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_l, GAME_INPUT_HEAVY_KICK));

    //_alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_LSHIFT, GAME_INPUT_GUARD));
    //_alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_LCTRL, GAME_INPUT_GRAB));

    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_q, GAME_INPUT_GUARD));
    _alias[PLAYER_INDEX_ONE].insert(pair<SDLKey, GameInput>(SDLK_e, GAME_INPUT_GRAB));

    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_UP, GAME_INPUT_UP));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_LEFT, GAME_INPUT_LEFT));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_DOWN, GAME_INPUT_DOWN));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_RIGHT, GAME_INPUT_RIGHT));
    
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_KP8, GAME_INPUT_LIGHT_PUNCH));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_KP4, GAME_INPUT_LIGHT_KICK));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_KP9, GAME_INPUT_HEAVY_KICK));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_KP5, GAME_INPUT_HEAVY_PUNCH));
    
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_RSHIFT, GAME_INPUT_GUARD));
    _alias[PLAYER_INDEX_TWO].insert(pair<SDLKey, GameInput>(SDLK_RCTRL, GAME_INPUT_GRAB));

/*

    // North <=> North-East, North <=> North-West

    addExclusive(GAME_INPUT_NORTH, GAME_INPUT_NORTH_EAST);
    addExclusive(GAME_INPUT_NORTH, GAME_INPUT_NORTH_WEST);

    // South <=> South-East, South <=> South-West

    addExclusive(GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST);
    addExclusive(GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST);

    // East <=> South-East, East <=> North-East

    addExclusive(GAME_INPUT_EAST, GAME_INPUT_NORTH_EAST);
    addExclusive(GAME_INPUT_EAST, GAME_INPUT_SOUTH_EAST);

    // West <=> South-West, West <=> North-West

    addExclusive(GAME_INPUT_WEST, GAME_INPUT_NORTH_WEST);
    addExclusive(GAME_INPUT_WEST, GAME_INPUT_SOUTH_WEST);

    // North <=> South, East <=> West


    // North-West <=> South-East, North-East <=> South-West

    addExclusive(GAME_INPUT_NORTH_EAST, GAME_INPUT_SOUTH_WEST);
    addExclusive(GAME_INPUT_SOUTH_WEST, GAME_INPUT_NORTH_EAST);
    */

    addExclusive(GAME_INPUT_NORTH, GAME_INPUT_SOUTH);
    addExclusive(GAME_INPUT_EAST,  GAME_INPUT_WEST);

    _simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_NORTH_EAST, makeVector<GameInput>(2, GAME_INPUT_NORTH, GAME_INPUT_EAST)));
    _simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_NORTH_WEST, makeVector<GameInput>(2, GAME_INPUT_NORTH, GAME_INPUT_WEST)));
    _simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_SOUTH_EAST, makeVector<GameInput>(2, GAME_INPUT_SOUTH, GAME_INPUT_EAST)));
    _simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_SOUTH_WEST, makeVector<GameInput>(2, GAME_INPUT_SOUTH, GAME_INPUT_WEST)));

    _consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_QCF, makeVector<GameInput>(3, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST, GAME_INPUT_EAST)));
    _consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_QCB, makeVector<GameInput>(3, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST)));
    _consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_HCF, makeVector<GameInput>(5, GAME_INPUT_WEST,  GAME_INPUT_SOUTH_WEST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST, GAME_INPUT_EAST)));
    _consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_HCB, makeVector<GameInput>(5, GAME_INPUT_EAST,  GAME_INPUT_SOUTH_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST)));
    
    _consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_DRAGON_FIST_FORWARD,  makeVector<GameInput>(3, GAME_INPUT_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST)));
    _consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_DRAGON_FIST_BACKWARD, makeVector<GameInput>(3, GAME_INPUT_WEST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST)));

    _inputBufferIgnore = makeVector<GameInput>(10, GAME_INPUT_UP, GAME_INPUT_DOWN, GAME_INPUT_LEFT, GAME_INPUT_RIGHT, GAME_INPUT_QCF, GAME_INPUT_QCB, GAME_INPUT_HCF, GAME_INPUT_HCB, GAME_INPUT_DRAGON_FIST_FORWARD, GAME_INPUT_DRAGON_FIST_BACKWARD);
    _eightWayDir = makeVector<GameInput>(8, GAME_INPUT_NORTH, GAME_INPUT_NORTH_EAST, GAME_INPUT_EAST, GAME_INPUT_SOUTH_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST, GAME_INPUT_NORTH_WEST);

    for (unsigned int index = 0; index < _maxPlayers; ++index)
    {
        PlayerIndex playerIndex = (PlayerIndex)index; 

        _inputStates.insert(pair<PlayerIndex, map<GameInput, InputState>>(playerIndex, map<GameInput, InputState>()));

        for (int i = 0; i < NUM_GAME_INPUTS; ++i)
        {
            _inputStates[playerIndex].insert(InputPair((GameInput)i, InputState()));
        }

        _keyStates.insert(pair<PlayerIndex, map<SDLKey, bool>>(playerIndex, map<SDLKey, bool>()));

        map<SDLKey, GameInput>::iterator it;
        for (it = _alias[playerIndex].begin(); it != _alias[playerIndex].end(); ++it)
        {
            _keyStates[playerIndex].insert(pair<SDLKey, bool>(it->first, false));
        }
    }

    _sdlKeys = SDL_GetKeyState(nullptr);

    stringstream ss;

    ss << "Detected " << SDL_NumJoysticks() << " Joysticks";
    INF(toString(), ss.str());
    ss.str(string());

    SDL_JoystickEventState(SDL_ENABLE);

    for (int i = 0; i < SDL_NumJoysticks(); i++) 
    {
        ss << "Joystick " << i << "s Name: " << SDL_JoystickName(i);
        INF(toString(), ss.str());
        ss.str(string());

        _joysticks.push_back(SDL_JoystickOpen(i));
    }

    INF(toString(), "Finished Init");
}

void InputSystem::term( void )
{
    gpEventDispatcher->removeEventListener(Event::EVENT_ENTER_FRAME, this, &InputSystem::update);

    for (int i = 0; i < _joysticks.size(); i++)
    {
        SDL_JoystickClose(_joysticks[i]);
    }
}

std::string InputSystem::toString( void ) const
{
    return "Input System";
}

void InputSystem::update( const Event& event )
{
    const FrameData* frameData = event.dataAs<FrameData>();

    SDL_Event inputEvent;
    SDLKey key;
    InputChange change;

    while (SDL_PollEvent(&inputEvent))
    {
        switch (inputEvent.type)
        {
        case SDL_KEYDOWN:

            if (inputEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                gpEventDispatcher->dispatchEvent(Event(Event::EVENT_GAME_END));
            }

            break;
        case SDL_QUIT:

            gpEventDispatcher->dispatchEvent(Event(Event::EVENT_GAME_END));

            break;
        case SDL_JOYBUTTONDOWN:

            if (inputEvent.jbutton.button == 8)
            {
                gpEventDispatcher->dispatchEvent(Event(Event::EVENT_GAME_END));
            }

            break;
        }
    }

    for (unsigned int index = 0; index < _maxPlayers; ++index)
    {
        PlayerIndex playerIndex = (PlayerIndex)index;

        map<SDLKey, GameInput>::iterator it;
        for (it = _alias[playerIndex].begin(); it != _alias[playerIndex].end(); ++it)
        {
            SDLKey key = it->first;

            bool 
                down     = (bool)_sdlKeys[key],
                wasDown  = _keyStates[playerIndex][key],
                pressed  = false,
                released = false;

            if (down && !wasDown)
            {
                pressed = true;
            }
            else if (!down && wasDown)
            {
                released = true;
            }

            if (pressed || released)
            {
                change = InputChange(key);
                change.Pressed = pressed;
                change.Released = released;

                _keyStates[playerIndex][key] = (bool)_sdlKeys[key];

                _inputChanges.push(change);
            }
        }

    }

    process(frameData);
}

void InputSystem::process( const FrameData* frameData )
{
    InputChange
        change;

    GameInput
        input;

    InputState
        *pState;

    map<GameInput, InputState>::iterator        itStates;
    map<GameInput, vector<GameInput>>::iterator itMulti;

    while (_inputChanges.size() > 0)
    {
        change = _inputChanges.back();
        _inputChanges.pop();

        for (unsigned int index = 0; index < _maxPlayers; ++index)
        {
            PlayerIndex playerIndex = (PlayerIndex)index;
            
            if (!mapContainsKey(_alias[playerIndex], change.Key))
                continue;

            input = _alias[playerIndex][change.Key];

            if (change.Pressed)
            {
                press(input, playerIndex);
            }
            else if (change.Released)
            {
                release(input, playerIndex);
            }
        }
    }

    for (unsigned int index = 0; index < _maxPlayers; ++index)
    {
        PlayerIndex playerIndex = (PlayerIndex)index; 

        for (itStates = _inputStates[playerIndex].begin(); itStates != _inputStates[playerIndex].end(); ++itStates)
        {
            itStates->second.Hidden = false;
        }

        GameInput 
            direction = INVALID_GAME_INPUT;

        bool
            up    = getInputState(GAME_INPUT_UP, playerIndex)->Down,
            down  = getInputState(GAME_INPUT_DOWN, playerIndex)->Down,
            left  = getInputState(GAME_INPUT_LEFT, playerIndex)->Down,
            right = getInputState(GAME_INPUT_RIGHT, playerIndex)->Down;

        if (up)
        {
            if (left)
            {
                direction = GAME_INPUT_NORTH_WEST;
            }
            else if (right)
            {
                direction = GAME_INPUT_NORTH_EAST;
            }
            else
            {
                direction = GAME_INPUT_NORTH;
            }
        }
        else if (down)
        {
            if (left)
            {
                direction = GAME_INPUT_SOUTH_WEST;
            }
            else if (right)
            {
                direction = GAME_INPUT_SOUTH_EAST;
            }
            else
            {
                direction = GAME_INPUT_SOUTH;
            }
        }
        else if (left)
        {
            direction = GAME_INPUT_WEST;
        }
        else if (right)
        {
            direction = GAME_INPUT_EAST;
        }

        for (unsigned int i = 0; i < _eightWayDir.size(); ++i)
        {
            pState = getInputState(_eightWayDir[i], playerIndex);

            if (direction == _eightWayDir[i])
            {
                press(_eightWayDir[i], playerIndex);
            }
            else
            {
                release(_eightWayDir[i], playerIndex);
            }
        }

        float maxDeltaTime = 0.5f;

        for (itMulti = _consecutive.begin(); itMulti != _consecutive.end(); ++itMulti)
        {
            input = itMulti->first;
            pState = getInputState(input, playerIndex);

            if (pState == nullptr)
                continue;

            release(input, playerIndex);

            if (_inputBuffer[playerIndex].size() < itMulti->second.size())
                continue;

            vector<GameInput> inputOrder = itMulti->second;
            bool combo = true;

            for (unsigned int i = 1; i < inputOrder.size(); ++i)
            {
                if (_inputBuffer[playerIndex][i].Time - _inputBuffer[playerIndex][i - 1].Time > maxDeltaTime)
                {
                    combo = false;
                    break;
                }
            }

            if (!combo)
                continue;

            for (unsigned int i = 0; i < inputOrder.size(); ++i)
            {
                if (_inputBuffer[playerIndex][i].Input != inputOrder[i])
                {
                    combo = false;
                    break;
                }
            }

            if (!combo)
                continue;

            for (unsigned int i = 0; i < inputOrder.size(); ++i)
                vectorRemoveAt(_inputBuffer[playerIndex], 0);

            press(input, playerIndex);
        }

        for (itStates = _inputStates[playerIndex].begin(); itStates!= _inputStates[playerIndex].end(); ++ itStates)
        {
            InputState state = itStates->second;
            input = itStates->first;

            // Catch strays
            SDLKey key = SDLK_UNKNOWN;

            map<SDLKey, GameInput>::iterator it;
            for (it = _alias[playerIndex].begin(); it != _alias[playerIndex].end(); ++it)
            {
                if (it->second == input)
                {
                    key = it->first;
                    break;
                }
            }

            if (key != SDLK_UNKNOWN)
            {
                if (state.Down && !_keyStates[playerIndex][key])
                {
                    release(input, playerIndex);
                }
            }

            if (state.Hidden)
                continue;

            if (state.Down)
            {
                gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_HELD, InputData(input, playerIndex)));
            }

            if (state.Pressed)
            {
                itStates->second.Pressed = false;
                gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_PRESSED, InputData(input, playerIndex)));
            }
            else if (state.Released)
            {
                itStates->second.Released = false;
                gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_RELEASED, InputData(input, playerIndex)));
            }
        }

    }

}

void InputSystem::press( const GameInput input, const PlayerIndex index )
{
    InputState* pState = getInputState(input, index);

    if (pState == nullptr)
        return;

    if (pState->Down)
        return;

    addInputToBuffer(input, index);

    pState->Pressed = true;
    pState->Released = false;
    pState->Down = true;
}

void InputSystem::release( const GameInput input, const PlayerIndex index )
{
    InputState* pState = getInputState(input, index);

    if (pState == nullptr)
        return;

    if (!pState->Down)
        return;

    pState->Pressed = false;
    pState->Released = true;
    pState->Down = false;
}

void InputSystem::addExclusive( const GameInput first, const GameInput second )
{
    _exclusive.insert(pair<GameInput, GameInput>(first,  second));
    _exclusive.insert(pair<GameInput, GameInput>(second, first));
}

InputState * InputSystem::getInputState( GameInput input, const PlayerIndex index )
{
    if (!mapContainsKey(_inputStates[index], input))
        return nullptr;

    return &_inputStates[index][input];
}

void InputSystem::addInputToBuffer( GameInput input, const PlayerIndex index )
{
    if (!vectorContains(_inputBufferIgnore, input))
    {
        _inputBuffer[index].push_back(InputPress(input));
    }

    while (_inputBuffer.size() > INPUT_BUFFER_MAX)
        vectorRemoveAt(_inputBuffer[index], 0);
}
