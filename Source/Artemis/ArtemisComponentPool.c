/**
* The primary instance for the framework. It contains all the managers.
* 
* You must use this to create, delete and retrieve entities.
* 
* It is also important to set the delta each game loop iteration, and initialize before game loop.
* 
* @author Arni Arent
* 
*/
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisComponentPool);

ArtemisComponentPoolRef method Ctor(ArtemisComponentPoolRef this)
{
    this->pools = CFCreate(CFArray, CFCreate(CFArray, nullptr), nullptr);
    return this;
}

CFObjectRef ArtemisComponentPoolObtain(ArtemisComponentPoolRef this, CFClassRef cls, ArtemisComponentTypeRef type)
{
    (ArtemisComponentPoolRef)this;
    (CFClassRef)cls;
    (ArtemisComponentTypeRef)type;
    return nullptr;
}

void ArtemisComponentPoolFree(ArtemisComponentPoolRef this, CFObjectRef component, ArtemisComponentTypeRef type)
{
    (ArtemisComponentPoolRef)this;
    (CFObjectRef)component;
    (ArtemisComponentTypeRef)type;
}

void ArtemisComponentPoolFreeByIndex(ArtemisComponentPoolRef pool, CFObjectRef component, ulong typeIndex)
{
    (ArtemisComponentPoolRef)pool;
    (CFObjectRef)component;
    (ulong)typeIndex;
}

