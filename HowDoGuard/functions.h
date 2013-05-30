
#pragma once

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Defines.h"

#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <cstdarg>
#include <ctime>
#include <vector>
#include <map>

#define PI  3.14159
#define PI2 6.28318

#define TO_RAD (PI / 180.0)
#define TO_DEG (180.0 / PI)

using namespace std;

#ifdef DEBUG

    #define ERR(SRC, MSG) \
        cerr << "[" << SRC << "] Error: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

    #define INF(SRC, MSG) \
        cout << "[" << SRC << "] Info: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

#else

    #define ERR(SRC, MSG)
    #define INF(SRC, MSG)

#endif

inline void initRandom( void ) { srand( unsigned(time(nullptr)) ); }
inline int randInt( int min, int max ) { return min + (rand() % (max - min + 1)); }

inline float floor  (float value, int accuracy) { int mult = 10 * accuracy; return floorf(value * mult)        / mult; }
inline float nearest(float value, int accuracy) { int mult = 10 * accuracy; return floorf(value * mult + 0.5f) / mult; }
inline float ceil   (float value, int accuracy) { int mult = 10 * accuracy; return ceilf (value * mult)        / mult; }

inline double floor  (double value, int accuracy) { int mult = 10 * accuracy; return floor(value * mult)       / mult; }
inline double nearest(double value, int accuracy) { int mult = 10 * accuracy; return floor(value * mult + 0.5) / mult; }
inline double ceil   (double value, int accuracy) { int mult = 10 * accuracy; return ceil (value * mult)       / mult; }

template <class Number>
inline Number approach( Number value, Number target, Number speed )
{
    return ( ( value > target )
        ? max( value - speed, target )
        : min( value + speed, target )
        );
}

template <class Number>
inline Number reduce( Number value, Number speed )
{
    return ( ( value > 0 )
        ? max( value - speed, 0 )
        : min( value + speed, 0 )
        );
}

template <class Number>
inline Number clamp(Number value, Number min, Number max) { return ( ( value > max ) ? max : ( ( value < min ) ? min : value ) ); }

template <class Number>
inline Number lerp( Number start, Number end, float fraction) { return ( start + (end - start) * fraction ); }

template <class Number>
inline int sign( Number value ) { return ( value > 0 ? 1 : ( value < 0 ? -1 : 0 ) ); }

template <class Number>
inline bool inBounds( Number value, Number min, Number max ) { return ( value >= min && value <= max); }

template <typename T>
inline bool isType( const void* object ) { return ( const T* convert = dynamic_cast<const T*>(object) ); }

inline time_t now( void ) { return time((time_t*)0); }

vector<string> strSplit( string str, char sep, int limit = -1 );
string strReplace   ( string str, const string& sub, const string& newStr );
string strReplaceAll( string str, const string& sub, const string& newStr );

string basename(string fullPath);

inline float toRad( float deg ) { return (float)( deg * TO_RAD ); }
inline float toDeg( float rad ) { return (float)( rad * TO_DEG ); };

int    toInt   ( const string& value );
float  toFloat ( const string& value );
double toDouble( const string& value );

template <class Number>
string numToString( const Number& value )
{
    stringstream ss;
    ss << value;
    return ss.str();
}

void delay( int millis );
void die  ( int errorLevel = 0 );
void pause( void );

template <typename Value>
bool arrayContains(unsigned int size, const Value list[], const Value& element)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (list[i] == element)
            return true;
    }

    return false;
}

template <typename Value>
int arrayIndexOf(unsigned int size, const Value list[], const Value& element)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (list[i] == element)
            return i;
    }

    return -1;
}

template <typename Value>
vector<Value> makeVector( int count, Value first, ...)
{
    va_list mark;
    vector<Value> newVector;

    newVector.push_back(first);

    va_start(mark, first);
    for (int i = 0; i < count - 1; ++i)
    {
        newVector.push_back(va_arg(mark, Value));
    }

    va_end(mark);

    return newVector;
}

template <typename Value>
bool vectorContains( const vector<Value>& list, const Value& element )
{
    vector<Value>::const_iterator it = list.cbegin();

    while (it != list.cend())
    {
        if (*it == element)
            return true;
        ++it;
    }

    return false;
}

template <typename Value>
int vectorIndexOf( const vector<Value>& list, const Value& element )
{
    vector<Value>::const_iterator it = list.cbegin();

    int i = 0;
    while (it != list.cend())
    {
        if (*it == element)
            return i;
        ++it;
        ++i;
    }

    return -1;
}

template <typename Value>
bool vectorRemove( vector<Value>& list, const Value& element )
{
    vector<Value>::iterator it = list.begin();

    while (it != list.end())
    {
        if (*it == element)
        {
            list.erase(it);
            return true;
        }
        ++it;
    }

    return false;
}

template <typename Value>
bool vectorRemoveAt( vector<Value>& list, const int index )
{
    if (inBounds(index, 0, (int)list.size()))
    {
        list.erase(list.begin() + index);
        return true;
    }

    return false;
}

template <typename Value>
inline void vectorRemoveAll( vector<Value>& list, const Value& element )
{
    while (vectorRemove(list, element));
}

template <class Key, class Value>
bool mapContainsKey( const map<Key, Value>& collection, Key key)
{
    return ( collection.find(key) != collection.cend() );
}

template <class Key, class Value>
bool mapRemoveKey( map<Key, Value>& collection, Key key )
{
    map<Key, Value>::iterator it;

    it = collection.find(key);
    if (it != collection.end())
    {
        collection.erase(it);
        return true;
    }

    return false;
}

template <class Key, class Value>
bool mapContainsValue( const map<Key, Value>& collection, Value value )
{
    map<Key, Value>::const_iterator it;

    for (it = collection.cbegin(); it != collection.cend(); ++it)
    {
        if (it->second == value)
            return true;
    }

    return false;
}

template <class Key, class Value>
Key mapFindKey( const map<Key, Value>& collection, Value value)
{
    map<Key, Value>::const_iterator it;

    for (it = collection.cbegin(); it != collection.cend(); ++it)
    {
        if (it->second == value)
            return it->first;
    }

    return Key();
}

template <class Key, class Value>
bool mapRemoveValue( map<Key, Value>& collection, Value value)
{
    map<Key, Value>::iterator it;

    for (it = collection.begin(); it != collection.end(); ++it)
    {
        if (it->second == value)
        {
            collection.erase(it);
            return true;
        }
    }

    return false;
}

#endif 