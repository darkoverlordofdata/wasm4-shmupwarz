#include "../artemis.h"
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
typedef struct __ArtemisComponentPool {
    __CFObject  obj;
    CFBagRef    pools;
} __ArtemisComponentPool;

static struct __CFClass class = {
    .name = "ArtemisComponentPool",
    .size = sizeof(struct __ArtemisComponentPool),
    .ctor = ctor,
};
CFClassRef ArtemisComponentPool = &class;

static bool ctor(void *ptr, va_list args)
{
    (void*)args;
    ArtemisComponentPoolRef this = ptr;

    this->pools = CFCreate(CFArray, CFCreate(CFArray, NULL), NULL);
    return true;
}

CFObjectRef ArtemisComponentPoolObtain(ArtemisComponentPoolRef this, CFClassRef cls, ArtemisComponentTypeRef type)
{
    (void*)this;
    (void*)cls;
    (void*)type;
    return NULL;
}

void ArtemisComponentPoolFree(ArtemisComponentPoolRef this, CFObjectRef component, ArtemisComponentTypeRef type)
{
    (void*)this;
    (void*)component;
    (void*)type;
}

void ArtemisComponentPoolFreeByIndex(ArtemisComponentPoolRef pool, CFObjectRef component, ulong typeIndex)
{
    (void*)pool;
    (void*)component;
    (void*)typeIndex;
}

