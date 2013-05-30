#include "MemoryTracker.h"

int MemoryTracker::_sAllocationIndex = 0;
MemoryTracker* gpMemoryTracker;

MemoryTracker::MemoryTracker( void )
{
}

MemoryTracker::~MemoryTracker( void )
{

#ifdef DEBUG

    INF(toString(), "Final Allocations");
    printAllocations();

#endif

    killSurvivors();

}

std::string MemoryTracker::toString( void ) const
{
    return "Memory Tracker";
}

void MemoryTracker::addAllocation( GameObject *ptr, size_t size, int lineNumber, char *filename )
{
    map<GameObject*, AllocationRecord>::iterator it = _allocations.find(ptr);
    
    if (it != _allocations.end())
    {
        ERR(toString(), "Element already in map");
    }
    else
    {
        if (_sAllocationIndex == 186 || _sAllocationIndex == 188)
        {
            cout << "wat" << endl;
        }

        AllocationRecord rec(_sAllocationIndex, size, lineNumber, string(filename));

        pair<GameObject*, AllocationRecord> newPair(ptr, rec);
        _allocations.insert(newPair);

        ++_sAllocationIndex;
    }
}

bool MemoryTracker::removeAllocation( GameObject *ptr )
{
    if (_allocations.size() == 0)
        return false;

    map<GameObject*, AllocationRecord>::iterator it = _allocations.find(ptr);

    if (it == _allocations.end())
    {
        return false;
    }
    else
    {
        _allocations.erase(it);
    }

    return true;
}

int MemoryTracker::numAllocations( void )
{
    return _allocations.size();
}

void MemoryTracker::printAllocations( void )
{
    printAllocations(cout);
}

void MemoryTracker::printAllocations( ostream& stream )
{
    stream << "Allocations: \n";

    map<GameObject*, AllocationRecord>::iterator it;
    for (it = _allocations.begin(); it != _allocations.end(); ++it)
    {
        stream << "#" << it->second.Num
               << ": (address: #" << it->first << ") "
               << it->first->toString() << "\n";

        stream << "\t In " << basename(it->second.Filename)
               << " On Line " << it->second.LineNum << "\n";
    }
}

void MemoryTracker::killSurvivors( void )
{
    vector<GameObject*> survivors;

    map<GameObject*, AllocationRecord>::iterator it;
    for (it = _allocations.begin(); it != _allocations.end(); ++it)
        survivors.push_back(it->first);

    for (unsigned int i = 0; i < survivors.size(); ++i)
        delete survivors[i];
}
