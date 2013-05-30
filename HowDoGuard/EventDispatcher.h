#pragma once

#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include "Common.h"
#include "GameObject.h"

#include "Event.h"
#include "Delegate.h"
#include <map>
#include <vector>

typedef Delegate<void, const Event&> EventDelegate;
typedef vector<EventDelegate*> EventListenerList;
typedef map<EventType, EventListenerList> EventMap;

class EventDispatcher
    : public GameObject
{
private:

    EventMap
        _eventMap;

    bool
        _changed;

    static vector<EventDispatcher*>
        _sDispatchers;

    void cleanMap( void );

    virtual void doNothing( void ) { }

public:

    EventDispatcher( void );
    virtual ~EventDispatcher( void );

    virtual string toString( void ) const;

    void addEventListener   ( const EventType& eventType, const EventDelegate& functionDelegate );
    void removeEventListener( const EventType& eventType, const EventDelegate& functionDelegate );

    void addEventListener   ( const EventType& eventType, void (*function)(const Event&));
    void removeEventListener( const EventType& eventType, void (*function)(const Event&));

    template <typename ObjectType, typename Method>
    void addEventListener( const EventType& eventType, ObjectType* object, Method method);

    template <typename ObjectType, typename Method>
    void removeEventListener( const EventType& eventType, ObjectType* object, Method method);

    template <typename ObjectType>
    void removeAllMethods( ObjectType* object );

    void removeAllListeners( void );
    void removeAllListeners( const EventType& eventType );

    void dispatchEvent( Event& event );

    static void cleanEvents( void )
    {
        int length = _sDispatchers.size();
        for (int i = 0; i < length; ++i)
            _sDispatchers[i]->cleanMap();
    }

};

extern EventDispatcher* gpEventDispatcher;

template <typename ObjectType, typename Method>
void EventDispatcher::addEventListener( const EventType& eventType, ObjectType* object, Method method )
{
    addEventListener(eventType, EventDelegate(object, method));
}

template <typename ObjectType, typename Method>
void EventDispatcher::removeEventListener( const EventType& eventType, ObjectType* object, Method method )
{
    removeEventListener(eventType, EventDelegate(object, method));
}

template <typename ObjectType>
void EventDispatcher::removeAllMethods( ObjectType* object )
{
    bool needRepeat = true;
    EventMap::iterator mapIter;
    EventListenerList::iterator listIter;

    while(needRepeat)
    {
        needRepeat = false;
        for(mapIter = _eventMap.begin(); !needRepeat && mapIter != _eventMap.end(); ++mapIter)
        {
            for(listIter = mapIter->second.begin(); !needRepeat && listIter != mapIter->second.end(); ++listIter)
            {
                if ( *listIter == nullptr )
                    continue;

                if ( (*listIter)->isMethodOf(object) )
                {
                    (*listIter) = nullptr;
                    needRepeat = true;
                    break;
                }
            }
        }
    }
}

#endif