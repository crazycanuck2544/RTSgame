#include "Event.h"

const EventType Event::EVENT_NULL          = "null";
const EventType Event::EVENT_ENTER_FRAME  = "enterFrame";
const EventType Event::EVENT_FRAME          = "frame";
const EventType Event::EVENT_EXIT_FRAME      = "exitFrame";
const EventType Event::EVENT_RENDER_START = "renderStart";
const EventType Event::EVENT_RENDER          = "render";
const EventType Event::EVENT_RENDER_END      = "renderEnd";
const EventType Event::EVENT_GAME_START      = "gameStart";
const EventType Event::EVENT_GAME_END      = "gameEnd";

const EventData Event::BLANK_DATA  = EventData();
const Event        Event::BLANK_EVENT = Event(EVENT_NULL, BLANK_DATA);

Event::Event( const EventType &type /*= EVENT_NULL*/, const EventData &data /*= BLANK_DATA*/ )
{
    _type = type;
    _pData = data.clone();
}

Event::Event( const Event &rhs )
{
    _type = rhs._type;
    _pData = (rhs._pData != nullptr ? rhs._pData->clone() : nullptr);
}

Event::~Event( void )
{
    if (_pData != nullptr)
        delete _pData;
}

std::string Event::toString( void ) const
{
    return "Event";
}
