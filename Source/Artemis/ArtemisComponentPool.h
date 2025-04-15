#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisComponentPool
 */
extern CFClassRef ArtemisComponentPool;

typedef struct __ArtemisComponentPool* ArtemisComponentPoolRef;
typedef struct __ArtemisComponentType* ArtemisComponentTypeRef;

CFObjectRef ArtemisComponentPoolObtain(ArtemisComponentPoolRef, CFClassRef, ArtemisComponentTypeRef);
void ArtemisComponentPoolFree(ArtemisComponentPoolRef, CFObjectRef, ArtemisComponentTypeRef);
void ArtemisComponentPoolFreeByIndex(ArtemisComponentPoolRef, CFObjectRef, ulong);

