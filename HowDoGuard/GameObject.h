#pragma once

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class GameObject
{
private:

public:

    GameObject( void );
    virtual ~GameObject( void );

    virtual string toString( void ) const = 0;

    friend ostream& operator<<( ostream& os, const GameObject& go );

    void* operator new(size_t size);
    void* operator new[](size_t size);

    void* operator new(size_t pSize, int pLineNumber, char *pFilename);
    void* operator new[](size_t pSize, int pLineNumber, char *pFilename);

    void operator delete(void *ptr);
    void operator delete[](void *ptr);

    void operator delete(void *pPtr, int pLineNumber, char *pFilename);
    void operator delete[](void *pPtr, int pLineNumber, char *pFilename);

#ifdef DEBUG

#define New new(__LINE__, __FILE__)

#else

#define New new

#endif

};

#endif