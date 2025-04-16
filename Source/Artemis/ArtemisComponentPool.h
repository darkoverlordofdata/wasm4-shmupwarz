#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisComponentPool
 */
extern CFClassRef ArtemisComponentPool;

typedef struct __ArtemisComponentPool {
    __CFObject  obj;
    CFBagRef    pools;
} __ArtemisComponentPool;

typedef struct __ArtemisComponentPool* ArtemisComponentPoolRef;
typedef struct __ArtemisComponentType* ArtemisComponentTypeRef;

ArtemisComponentPoolRef method Ctor(ArtemisComponentPoolRef);
CFObjectRef ArtemisComponentPoolObtain(ArtemisComponentPoolRef, CFClassRef, ArtemisComponentTypeRef);
void ArtemisComponentPoolFree(ArtemisComponentPoolRef, CFObjectRef, ArtemisComponentTypeRef);
void ArtemisComponentPoolFreeByIndex(ArtemisComponentPoolRef, CFObjectRef, ulong);

static inline ArtemisComponentPoolRef NewArtemisComponentPool()
{
    return Ctor((ArtemisComponentPoolRef)CFCreate(ArtemisComponentPool));
}
