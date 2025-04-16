#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisAspect
 */
extern CFClassRef ArtemisAspect;
typedef struct __ArtemisWorld*      ArtemisWorldRef;

typedef struct __ArtemisAspect {
    __CFObject      obj;
    CFBitVectorRef  allSet;
    CFBitVectorRef  exclusionSet;
    CFBitVectorRef  oneSet;
    ArtemisWorldRef world;
} __ArtemisAspect;

typedef struct __ArtemisAspect*     ArtemisAspectRef;

ArtemisAspectRef method Ctor(ArtemisAspectRef, ArtemisWorldRef);
void ArtemisAspectSetWorld(ArtemisAspectRef, ArtemisWorldRef);
CFBitVectorRef ArtemisAspectGetAllSet(ArtemisAspectRef);
CFBitVectorRef ArtemisAspectGetExclusionSet(ArtemisAspectRef);
CFBitVectorRef ArtemisAspectGetOneSet(ArtemisAspectRef);
ulong ArtemisAspectGetIndexFor(ArtemisAspectRef, CFClassRef);
ArtemisAspectRef ArtemisAspectAll(ArtemisAspectRef, ...);
ArtemisAspectRef ArtemisAspectExclude(ArtemisAspectRef, ...);
ArtemisAspectRef ArtemisAspectOne(ArtemisAspectRef, ...);

static inline ArtemisAspectRef NewArtemisAspect(ArtemisWorldRef world)
{
    return Ctor((ArtemisAspectRef)CFCreate(ArtemisAspect), world);
}