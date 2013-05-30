#include "DataManager.h"

DataManager* gpDataManager = nullptr;
ConfigLevel DataManager::_config = ConfigLevel();

DataManager::DataManager( void )
{
}

DataManager::~DataManager( void )
{
    term();
}

std::string DataManager::toString( void ) const
{
    return "Data Manager";
}

void DataManager::init( void )
{
    INF(toString(), "Starting Init");

    pAnimations = New Manager<Animation>();
    pAnimations->init();

    pSprites = New Manager<Sprite>();
    pSprites->init();

    pTextures = New Manager<Texture>();
    pTextures->init();

    reload();

    INF(toString(), "Finished Init");
}

void DataManager::term( void )
{
    delete pAnimations;
    delete pSprites;
    delete pTextures;
}

void DataManager::reload( void )
{
    _config.clear();

    pAnimations->clear();
    pSprites->clear();
    pTextures->clear();

    loadConfig("main.cfg");
}

void DataManager::loadConfig( string filename, vector<string> levels /*= vector<string>()*/ )
{
    ifstream file("assets/config/" + filename);

    string line = "";
    string listName = "";

    while (!file.eof())
    {
        getline(file, line);

        if (line.length() == 0 || line[0] == '#')
            continue;

        if (line[0] == '!')
        {
            vector<string> split = strSplit(line, ' ', 2);

            if (split.size() < 2)
                continue;

            if (split[0] == "!Load")
            {
                loadConfig(split[1], levels);
            }
            else if (split[0] == "!LoadAsset")
            {
                loadAssets(split[1]);
            }
            else if (split[0] == "!LoadState")
            {
                split = strSplit(split[1], ' ', 2);

                if (split.size() < 2)
                    continue;

                loadStates(split[0], split[1]);
            }
            else if (split[0] == "!Start")
            {
                levels.push_back(split[1]);
            }
            else if (split[0] == "!End")
            {
                levels.pop_back();
            }
            else if (split[0] == "!StartList")
            {
                listName = split[1];
            }
            else if (split[0] == "!EndList")
            {
                listName = "";
            }
        }
        else
        {
            parseConfigLine(line, levels, listName);
        }
    }

    file.close();
}

void DataManager::loadAssets( string filename )
{
    ifstream file("assets/config/" + filename);

    stringstream ss;
    string line;

    while (!file.eof())
    {
        getline(file, line);

        if (line.length() == 0 || line[0] == '#')
            continue;

        vector<string> pieces = strSplit(line, ' ', 2);

        if (pieces.size() == 2)
        {
            if (pieces[0] == "Texture")
            {
                ItemKey key = pieces[1];

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "File")
                {
                    ss.str("");
                    ss << "assets/sheets/" << pieces[1];
                    pTextures->addEmpty(key)->init(ss.str());
                }
                else
                    continue;
            }
            else if (pieces[0] == "Animation")
            {
                ItemKey key = pieces[1];
                ItemKey texKey = "";
                bool loop = false;
                int numFrames = -1;
                vector<Sprite*> frames;
                bool autoFrames = false;
                int framesPerRow = -1;
                Rect frameSize = Rect::ZERO;

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "Texture")
                {
                    texKey = pieces[1];
                }
                else
                    continue;

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "Loop")
                {
                    loop = (pieces[1][0] == 'T');
                }
                else
                    continue;

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "Frames")
                {
                    pieces = strSplit(pieces[1], ' ', 2);

                    if (pieces.size() == 1)
                    {
                        numFrames = toInt(pieces[0]);
                    }
                    else if (pieces.size() == 2)
                    {
                        numFrames = toInt(pieces[0]);

                        if (pieces[1] == "Auto")
                        {
                            autoFrames = true;
                        }
                    }
                }
                else
                    continue;

                if (numFrames == -1)
                    continue;

                if (autoFrames)
                {
                    do 
                    {
                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] == "FramesPerRow")
                        {
                            framesPerRow = toInt(pieces[1]);
                        }
                        else if (pieces[0] == "FrameSize")
                        {
                            pieces = strSplit(pieces[1], ' ', 2);

                            if (pieces.size() < 2)
                                continue;

                            frameSize = Rect(0, 0, toFloat(pieces[0]), toFloat(pieces[1]));
                        }
                    } 
                    while (line.length() != 0 && pieces[0] != "FrameOrder");

                    if (line.length() == 0)
                        return;

                    vector<Rect> tmpFrames;
                    Rect tmpRect = frameSize;

                    int col = 0;
                    for (int i = 0; i < numFrames; ++i)
                    {
                        tmpFrames.push_back(tmpRect);
                        tmpRect.X += frameSize.Width;
                        col++;
                        if (framesPerRow != -1 && col == framesPerRow)
                        {
                            col = 0;
                            tmpRect.X = 0;
                            tmpRect.Y += frameSize.Height;
                        }
                    }

                    int numFramesInOrder = toInt(pieces[1]);

                    for (int i = 0; i < numFramesInOrder; ++i)
                    {
                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] != "Frame")
                            continue;

                        pieces = strSplit(pieces[1], ' ', 2);

                        int rectInd = toInt(pieces[0]) - 1;
                        rectInd = clamp(rectInd, 0, (int)tmpFrames.size());
                        float speed = toFloat(pieces[1]);

                        Sprite *sprite = New Sprite();
                        sprite->init(pTextures->get(texKey), tmpFrames[rectInd], speed);

                        pSprites->add(sprite);

                        frames.push_back(sprite);
                    }
                }
                else
                {
                    for (int i = 0; i < numFrames; ++i)
                    {
                        Rect rect;
                        double speed;

                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] == "Rect")
                        {
                            pieces = strSplit(pieces[1], ' ', 4);
                            rect = Rect(toFloat(pieces[0]), toFloat(pieces[1]), toFloat(pieces[2]), toFloat(pieces[3]));
                        }
                        else
                            break;

                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] == "Speed")
                        {
                            speed = toFloat(pieces[1]);
                        }
                        else
                            break;

                        Sprite *sprite = New Sprite();
                        sprite->init(pTextures->get(texKey), rect, speed);

                        pSprites->add(sprite);

                        frames.push_back(sprite);
                    }
                }

                pAnimations->addEmpty(key)->init(frames, frameSize.size(), true, loop);
            }
        }
    }

    file.close();
}

void DataManager::loadStates( string filename, string stateName )
{
    ifstream file("assets/config/" + filename);

    PlayerStateMap data;

    GameInput input;
    GameInputType type;
    VerticalState vertState, newVertState;
    PlayerState before, after;
    string line;
    vector<string> pieces;
    pair<GameInput, GameInputType> inputTypePair;
    int index;

    while (!file.eof())
    {
        getline(file, line);

        if (line.length() == 0 || line[0] == '#')
            continue;

        pieces = strSplit(line, ' ', 2);

        if (pieces.size() < 2)
            continue;

        if (pieces[0] == "Input")
        {
            pieces = strSplit(pieces[1], ' ', 2);

            input = INVALID_GAME_INPUT;
            type = INVALID_GAME_INPUT_TYPE;

            index = arrayIndexOf(NUM_GAME_INPUTS, GAME_INPUT_NAMES, pieces[0]);
            if (index != -1)
            {
                input = (GameInput)index;
            }

            index = arrayIndexOf(NUM_GAME_INPUT_TYPES, GAME_INPUT_TYPE_NAMES, pieces[1]);
            if (index != -1)
            {
                type = (GameInputType)index;
            }

            if (input == INVALID_GAME_INPUT)
                continue;

            inputTypePair = pair<GameInput, GameInputType>(input, type);
            data.insert(pair<pair<GameInput, GameInputType>, VerticalPlayerStateMap>(inputTypePair, VerticalPlayerStateMap()));
        }
        else if (pieces[0] == "VertState")
        {
            index = arrayIndexOf(NUM_VERTICAL_STATES, VERTICAL_STATE_NAMES, pieces[1]);
            if (index != -1)
            {
                vertState = (VerticalState)index;
                data[inputTypePair].insert(pair<VerticalState, PlayerStateChangeList>(vertState, PlayerStateChangeList()));
            }
        }
        else if (pieces[0] == "AddState")
        {
            pieces = strSplit(pieces[1], ' ');

            if (pieces.size() < 2)
                continue;
            else if (pieces.size() == 2)
            {
                newVertState = vertState;
            }
            else
            {
                int index = arrayIndexOf(NUM_VERTICAL_STATES, VERTICAL_STATE_NAMES, pieces[2]);
                if (index != -1)
                {
                    newVertState = (VerticalState)index;
                }
            }

            index = arrayIndexOf(NUM_PLAYER_STATES, PLAYER_STATE_NAMES, pieces[0]);
            if (index != -1)
            {
                before = (PlayerState)index;
            }

            index = arrayIndexOf(NUM_PLAYER_STATES, PLAYER_STATE_NAMES, pieces[1]);
            if (index != -1)
            {
                after = (PlayerState)index;
            }

            data[inputTypePair][vertState].push_back(PlayerStateChange(before, after, newVertState));
        }
    }

    file.close();

    PlayerStateData.insert(pair<ItemKey, PlayerStateMap>(stateName, data));
}

void DataManager::parseConfigLine( string line, vector<string> levels, string listName )
{
    ConfigLevel *tmp = getLevel(levels);

    if (listName != "")
    {
        tmp->getList(listName)->push_back(line);
    }
    else
    {
        vector<string> parts = strSplit(line, ' ', 2);

        if (parts.size() < 2)
            return;

        tmp->addData(parts[0], parts[1]);
    }
}

ConfigValue DataManager::getData( vector<ConfigKey> name, ConfigKey dataName )
{
    ConfigLevel* tmp = getLevel(name);

    if (!tmp->containsData(dataName))
    {
        return "";
    }

    return tmp->getData(dataName);
}

vector<ConfigValue>* DataManager::getList( vector<ConfigKey> name, ConfigKey listName )
{
    ConfigLevel* tmp = getLevel(name);

    if (!tmp->containsList(listName))
    {
        tmp->addList(listName);
    }

    return tmp->getList(listName);
}

ConfigLevel* DataManager::getLevel( vector<ConfigKey> name )
{
    ConfigLevel* tmpLevel = &_config;

    for (unsigned int i = 0; i < name.size(); ++i)
    {
        if (name[i].length() == 0)
            break;

        if (!tmpLevel->containsLevel(name[i]))
        {
            tmpLevel->addLevel(name[i]);
        }

        tmpLevel = tmpLevel->getLevel(name[i]);
    }

    return tmpLevel;
}

std::string DataManager::getString( vector<ConfigKey> name )
{
    string itemName = name.back();

    name.pop_back();

    return getLevel(name)->getData(itemName);
}

int DataManager::getInt( vector<ConfigKey> name )
{
    string itemName = name.back();

    name.pop_back();

    return toInt(getLevel(name)->getData(itemName));
}

float DataManager::getFloat( vector<ConfigKey> name )
{
    string itemName = name.back();

    name.pop_back();

    return toFloat(getLevel(name)->getData(itemName));
}

double DataManager::getDouble( vector<ConfigKey> name )
{
    string itemName = name.back();

    name.pop_back();

    return toDouble(getLevel(name)->getData(itemName));
}

Vector2 DataManager::getVector2( vector<ConfigKey> name )
{
    return Vector2::ZERO;
}

Rect DataManager::getRect( vector<ConfigKey> name )
{
    return Rect::ZERO;
}

Circle DataManager::getCircle( vector<ConfigKey> name )
{
    return Circle::ZERO;
}

Color DataManager::getColor( vector<ConfigKey> name )
{
    return Color::WHITE;
}

vector<string> DataManager::getStringList( vector<ConfigKey> name )
{
    return vector<string>();
}

vector<int> DataManager::getIntList( vector<ConfigKey> name )
{
    return vector<int>();
}

vector<float> DataManager::getFloatList( vector<ConfigKey> name )
{
    return vector<float>();
}

vector<double> DataManager::getDoubleList( vector<ConfigKey> name )
{
    return vector<double>();
}

vector<Vector2> DataManager::getVector2List( vector<ConfigKey> name )
{
    return vector<Vector2>();
}

vector<Rect> DataManager::getRectList( vector<ConfigKey> name )
{
    return vector<Rect>();
}

vector<Circle> DataManager::getCircleList( vector<ConfigKey> name )
{
    return vector<Circle>();
}

vector<Color> DataManager::getColorList( vector<ConfigKey> name )
{
    return vector<Color>();
}
