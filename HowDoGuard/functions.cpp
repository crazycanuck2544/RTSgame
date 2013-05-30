
#include "functions.h"
#include "Timer.h"

void delay( int millis )
{
    Timer delayTimer = Timer();

    delayTimer.start();
    delayTimer.sleepUntilElapsed(millis);
}

vector<string> strSplit( string str, char sep, int limit /*= -1*/ )
{
    std::vector<std::string> stringParts;

    int stringLength = str.length();
    char currentChar;
    string tempString;

    for(int i = 0; i < stringLength; ++i)
    {
        currentChar = str[i];

        if (currentChar == sep)
        {
            tempString = str.substr(0, i);

            if (tempString.length() > 0)
            {
                stringParts.push_back(tempString);
            }

            str = str.substr(i + 1);
            stringLength = str.length();
            i = -1;

            if (limit != -1 && stringParts.size() == limit - 1)
            {
                stringParts.push_back(str);
                break;
            }
        }
        else if (i == stringLength - 1)
        {
            tempString = str.substr(0, i + 1);

            if ( tempString.length() > 0 )
            {
                stringParts.push_back(tempString);
            }

            str = "";
            stringLength = str.length();
            i = -1;

            if (limit != -1 && stringParts.size() == limit - 1)
            {
                stringParts.push_back(str);
                break;
            }
        }
    }

    return stringParts;
}

std::string strReplace( string str, const string& sub, const string& newStr )
{
    int pos = str.find(sub);

    if (pos == std::string::npos)
        return str;

    return str.replace(pos, sub.length(), newStr);
}

std::string strReplaceAll( string str, const string& sub, const string& newStr )
{
    int pos = str.find(sub);

    while (pos != std::string::npos)
    {
        str.replace(pos, sub.length(), newStr);
        pos = str.find(sub, pos + newStr.length());
    }

    return str;
}

int toInt( const string& value )
{
    stringstream ss(value);
    int result;
    return (ss >> result ? result : 0);
}

float toFloat( const string& value )
{
    stringstream ss(value);
    float result;
    return (ss >> result ? result : 0.0f);
}

double toDouble( const string& value )
{
    stringstream ss(value);
    double result;
    return (ss >> result ? result : 0.0);
}

string basename( string fullPath )
{
    char splitString = (fullPath.find("\\") != std::string::npos ? '\\' : '/');
    vector<std::string> parts = strSplit(fullPath, splitString);
    return parts[parts.size() - 1];
}

void die( int errorLevel /*= 0*/ )
{
    pause();
    exit(errorLevel);
}

void pause( void )
{
    cout << "Press any key to continue";
    _getch();
    cout << endl;
}