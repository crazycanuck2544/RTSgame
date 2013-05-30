#include "EventDispatcher.h"

EventDispatcher* gpEventDispatcher = nullptr;

vector<EventDispatcher*> EventDispatcher::_sDispatchers = vector<EventDispatcher*>();

EventDispatcher::EventDispatcher( void )
{
    _changed = false;
    _sDispatchers.push_back(this);
}

EventDispatcher::~EventDispatcher( void )
{
    vectorRemove(_sDispatchers, this);
    removeAllListeners();
}

std::string EventDispatcher::toString( void ) const
{
    return "Event Dispatcher";
}

void EventDispatcher::addEventListener( const EventType& eventType, const EventDelegate& functionDelegate )
{
    if (!mapContainsKey(_eventMap, eventType))
        _eventMap[eventType] = EventListenerList();

    int length = _eventMap[eventType].size();

    for(int i = 0; i < length; ++i)
    {
        if (_eventMap[eventType][i] == nullptr)
            continue;
        if (*(_eventMap[eventType][i]) == functionDelegate)
            return;
    }

    _eventMap[eventType].push_back(New EventDelegate(functionDelegate));
}

void EventDispatcher::removeEventListener( const EventType& eventType, const EventDelegate& functionDelegate )
{
    if (!mapContainsKey(_eventMap, eventType))
        return;

    int length = _eventMap[eventType].size();

    for(int i = 0; i < length; ++i)
    {
        if (_eventMap[eventType][i] == nullptr)
            continue;
        if (*(_eventMap[eventType][i]) == functionDelegate)
        {
            delete _eventMap[eventType][i];
            _eventMap[eventType][i] = nullptr;
            _changed = true;
            return;
        }
    }
}

void EventDispatcher::removeEventListener( const EventType& eventType, void (*function)(const Event&) )
{
    removeEventListener(eventType, EventDelegate(function));
}

void EventDispatcher::addEventListener( const EventType& eventType, void (*function)(const Event&) )
{
    addEventListener(eventType, EventDelegate(function));
}

void EventDispatcher::removeAllListeners( void )
{
    EventMap::iterator          mapIt;
    EventListenerList::iterator listIt;

    int length;
    for (mapIt = _eventMap.begin(); mapIt != _eventMap.end(); ++mapIt)
    {
        length = mapIt->second.size();
        for (int i = 0; i < length; ++i)
        {
            if (mapIt->second[i] != nullptr)
            {
                delete mapIt->second[i];
                mapIt->second[i] = nullptr;
            }
        }
    }

    _eventMap.clear();
}

void EventDispatcher::removeAllListeners( const EventType& eventType )
{
    if (!mapContainsKey(_eventMap, eventType))
        return;

    int length = _eventMap[eventType].size();
    for(int i = 0; i < length; ++i)
    {
        if ( _eventMap[eventType][i] != nullptr )
        {
            delete _eventMap[eventType][i];
            _eventMap[eventType][i] = nullptr;
        }
    }

    _eventMap.erase(eventType);

    _changed = true;
}

void EventDispatcher::dispatchEvent( Event& event )
{
    EventType type = event.type();

    if ( !mapContainsKey(_eventMap, type) )
        return;

    event.setTarget(this);

    unsigned int length = _eventMap[type].size();
    for(unsigned int i = 0; i < length; ++i)
    {
        if (_eventMap[type][i] != nullptr)
            _eventMap[type][i]->invoke(event);
    }
}

void EventDispatcher::cleanMap( void )
{
    if (!_changed)
        return;

    bool needRepeat = true;
    EventMap::iterator mapIt;
    EventListenerList* list;

    while (needRepeat)
    {
        needRepeat = false;
        for (mapIt = _eventMap.begin(); !needRepeat && mapIt != _eventMap.end(); ++mapIt)
        {
            list = &(mapIt->second);
            for (unsigned int i = 0; !needRepeat && i < list->size(); ++i)
            {
                if ((*list)[i] == nullptr)
                {
                    list->erase(list->begin() + i);
                    needRepeat = true;
                    break;
                }
            }
        }
    }

    _changed = false;
}
