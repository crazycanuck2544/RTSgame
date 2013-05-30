#include "GameObject.h"
#include "MemoryTracker.h"

GameObject::GameObject( void )
{
}

GameObject::~GameObject( void )
{
}

ostream& operator<<( ostream& os, const GameObject& go )
{
    os << go.toString();
    return os;
}

void *GameObject::operator new(size_t size)
{
    return malloc(size);
}
void *GameObject::operator new[](size_t size)
{
    return malloc(size);
}

void *GameObject::operator new(size_t size, int lineNumber, char *filename)
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((GameObject*)ptr, size, lineNumber, filename);
    return ptr;
}

void *GameObject::operator new[](size_t size, int lineNumber, char *filename)
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((GameObject*)ptr, size, lineNumber, filename);
    return ptr;
}

void GameObject::operator delete(void *ptr, int lineNumber, char *filename)
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void GameObject::operator delete[](void *ptr, int lineNumber, char *filename)
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void GameObject::operator delete(void *ptr)
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void GameObject::operator delete[](void *ptr)
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}