
#pragma once

#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "Common.h"

#include <map>

template <class T>
class Manager :
    public GameObject 
{

protected:

    map<ItemKey, T*> 
        *mObjects;

    static int
        mNextIndex;

    ItemKey getNextKey( void );

public:

    Manager( void );
    virtual ~Manager( void );

    virtual void init( void );
    virtual void term( void );

    virtual string toString( void ) const;

    bool      contains(ItemKey pItemKey);
    T        *add(ItemKey pItemKey, T *pObject);
    T        *addEmpty(ItemKey pItemKey);
    ItemKey   add(T *pObject);
    ItemKey   addEmpty( void );
    void      remove(ItemKey pItemKey);
    void      remove(T *pObject);
    T        *get(ItemKey pItemKey);
    int       size( void ) const;

    vector<T*> getAll( void );

    void clear( void ); 

};

template <class T>
int Manager<T>::mNextIndex = 0;

template <class T>
Manager<T>::Manager( void )
{
}

template <class T>
Manager<T>::~Manager( void )
{
    term();
}

template <class T>
ItemKey Manager<T>::getNextKey( void )
{
    ItemKey newKey;
    stringstream ss;
    do 
    {
        ss.str(string());
        ss.clear();
        ss << "auto-id" << mNextIndex;
        newKey = ss.str();

        ++mNextIndex;
    } 
    while (contains(newKey));

    return newKey;
}

template <class T>
void Manager<T>::init( void )
{
    mObjects = new map<ItemKey, T*>();
}

template <class T>
void Manager<T>::term( void )
{
    clear();
}

template <class T>
string Manager<T>::toString( void ) const
{
    return "Template Manager";
}

template <class T>
bool Manager<T>::contains(ItemKey pKey)
{
    for (map<ItemKey, T*>::iterator it = mObjects->begin(); it != mObjects->end(); ++it)
        if (it->first == pKey)
            return true;
    return false;
}

template <class T>
T *Manager<T>::add(ItemKey pKey, T *pObject)
{
    mObjects->insert(pair<ItemKey, T*>(pKey, pObject));
    return get(pKey);
}

template <class T>
T *Manager<T>::addEmpty(ItemKey pKey)
{
    mObjects->insert(pair<ItemKey, T*>(pKey, New T()));
    return get(pKey);
}

template <class T>
ItemKey Manager<T>::add( T *pObject )
{
    ItemKey nextKey = getNextKey();
    add(nextKey, pObject);
    return nextKey;
}

template <class T>
ItemKey Manager<T>::addEmpty( void )
{
    ItemKey nextKey = getNextKey();
    addEmpty(nextKey);
    return nextKey;
}

template <class T>
void Manager<T>::remove(ItemKey pKey)
{
    if (contains(pKey))
    {
        delete mObjects[pKey];
        mObjects[pKey] = nullptr;
        mObjects->erase(pKey);
    }
}

template <class T>
void Manager<T>::remove(T *pObject)
{
    ItemKey key;
    for (map<ItemKey, T*>::iterator it = mObjects->begin(); it != mObjects->end(); ++it)
        if (it->second == pObject)
            key = it->first;
    remove(key);
}

template <class T>
T *Manager<T>::get(ItemKey pKey)
{
    if (contains(pKey))
        return mObjects->at(pKey);
    else
    {
        stringstream ss;
        ss << "Tried to access a non existing item: " << pKey;
        ERR(toString(), ss.str());
        die();
        return nullptr;
    }
}

template <class T>
int Manager<T>::size( void ) const
{
    return mObjects->size();
}

template <class T>
vector<T*> Manager<T>::getAll( void )
{
    vector<T*> units;

    for (map<ItemKey, T*>::iterator it = mObjects->begin(); it != mObjects->end(); ++it)
        units.push_back(it->second);

    return units;
}

template <class T>
void Manager<T>::clear( void )
{
    for (map<ItemKey, T*>::iterator it = mObjects->begin(); it != mObjects->end(); ++it)
    {
        delete it->second;
        it->second = nullptr;
    }
    mObjects->clear();
}

#endif //__MANAGER_H__