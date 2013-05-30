#pragma once

#ifndef __MEMORY_TRACKER_H__
#define __MEMORY_TRACKER_H__

#include "Common.h"
#include "GameObject.h"

#include <map>

struct AllocationRecord
{

    int 
        Num,
        LineNum;

    size_t 
        Size;

    string
        Filename;

    AllocationRecord(int num, size_t size, int lineNum, string filename)
        : Num(num),
          Size(size),
          LineNum(lineNum),
          Filename(filename)
    {
    };

};

class MemoryTracker
    : public GameObject
{
private:

    static int
        _sAllocationIndex;

    map<GameObject*, AllocationRecord>
        _allocations;

    MemoryTracker(const MemoryTracker&);
    MemoryTracker& operator=(const MemoryTracker&);

public:

    MemoryTracker( void );
    virtual ~MemoryTracker( void );

    virtual string toString( void ) const;

    void addAllocation(GameObject *ptr, size_t size, int lineNumber, char *filename);
    bool removeAllocation(GameObject *ptr);

    int  numAllocations( void );

    void printAllocations( void );
    void printAllocations( ostream& stream );
    void killSurvivors( void );
};

extern MemoryTracker* gpMemoryTracker;

#endif