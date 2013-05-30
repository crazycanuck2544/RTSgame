#include "ConfigLevel.h"

ConfigLevel::ConfigLevel(void)
{
}

ConfigLevel::~ConfigLevel(void)
{
}

string ConfigLevel::toString( void ) const
{
    return "Config Level";
}

void ConfigLevel::clear( void )
{
    map<ConfigKey, vector<ConfigValue>>::iterator listsIt;
    map<ConfigKey, ConfigLevel>::iterator        levelsIt;

    _data.clear();

    for (listsIt = _lists.begin(); listsIt != _lists.end(); ++listsIt)
        listsIt->second.clear();

    _lists.clear();

    for (levelsIt = _levels.begin(); levelsIt != _levels.end(); ++levelsIt)
    {
        levelsIt->second.clear();
    }

    _levels.clear();
}

void ConfigLevel::addData( ConfigKey key, ConfigValue value )
{
    _data.insert(pair<ConfigKey, ConfigValue>(key, value));
}

vector<ConfigValue>* ConfigLevel::addList( ConfigKey key )
{
    _lists.insert(pair<ConfigKey, vector<ConfigValue>>(key, vector<ConfigValue>()));
    return getList(key);
}

ConfigLevel* ConfigLevel::addLevel( ConfigKey key )
{
    _levels.insert(pair<ConfigKey, ConfigLevel>(key, ConfigLevel()));
    return getLevel(key);
}

ConfigValue ConfigLevel::getData( ConfigKey key )
{
    if (containsData(key))
    {
        return _data[key];
    }
    return ConfigKey();
}

vector<ConfigValue>* ConfigLevel::getList( ConfigKey key )
{
    if (containsList(key))
    {
        return &_lists[key];
    }
    return nullptr;
}

ConfigLevel* ConfigLevel::getLevel( ConfigKey key )
{
    if (containsLevel(key))
    {
        return &_levels[key];
    }
    return nullptr;
}

vector<ConfigKey> ConfigLevel::getDataKeys( void )
{
    vector<ConfigKey> keys;

    map<ConfigKey, ConfigValue>::iterator it;

    for (it = _data.begin(); it != _data.end(); ++it)
    {
        keys.push_back(it->first);
    }

    return keys;
}

vector<ConfigKey> ConfigLevel::getListKeys( void )
{
    vector<ConfigKey> keys;

    map<ConfigKey, vector<ConfigValue>>::iterator it;

    for (it = _lists.begin(); it != _lists.end(); ++it)
    {
        keys.push_back(it->first);
    }

    return keys;
}

vector<ConfigKey> ConfigLevel::getLevelKeys( void )
{
    vector<ConfigKey> keys;

    map<ConfigKey, ConfigLevel>::iterator it;

    for (it = _levels.begin(); it != _levels.end(); ++it)
    {
        keys.push_back(it->first);
    }

    return keys;
}

bool ConfigLevel::containsData( ConfigKey key )
{
    return mapContainsKey(_data, key);
}

bool ConfigLevel::containsList( ConfigKey key )
{
    return mapContainsKey(_lists, key);
}

bool ConfigLevel::containsLevel( ConfigKey key )
{
    return mapContainsKey(_levels, key);
}
