#pragma once

#ifndef __CONFIG_LEVEL_H__
#define __CONFIG_LEVEL_H__

#include "Common.h"
#include "GameObject.h"

typedef string ConfigKey;
typedef string ConfigValue;

class ConfigLevel :
    public GameObject
{
private:

    map<ConfigKey, ConfigValue>
        _data;

    map<ConfigKey, vector<ConfigValue>>
        _lists;

    map<ConfigKey, ConfigLevel>
        _levels;

public:

    ConfigLevel( void );
    virtual ~ConfigLevel( void );

    virtual string toString( void ) const;

    void clear( void );

    void                 addData ( ConfigKey key, ConfigValue value );
    vector<ConfigValue>* addList ( ConfigKey key );
    ConfigLevel*         addLevel( ConfigKey key );
    
    ConfigValue          getData ( ConfigKey key );
    vector<ConfigValue>* getList ( ConfigKey key );
    ConfigLevel*         getLevel( ConfigKey key );

    vector<ConfigKey> getDataKeys ( void );
    vector<ConfigKey> getListKeys ( void );
    vector<ConfigKey> getLevelKeys( void );

    bool containsData ( ConfigKey key );
    bool containsList ( ConfigKey key );
    bool containsLevel( ConfigKey key );

};

#endif __CONFIG_LEVEL_H__