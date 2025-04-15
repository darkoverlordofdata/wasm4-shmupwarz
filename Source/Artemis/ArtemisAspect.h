#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisAspect
 */
extern CFClassRef ArtemisAspect;

typedef struct __ArtemisAspect*     ArtemisAspectRef;
typedef struct __ArtemisWorld*      ArtemisWorldRef;

void ArtemisAspectSetWorld(ArtemisAspectRef, ArtemisWorldRef);
CFBitVectorRef ArtemisAspectGetAllSet(ArtemisAspectRef);
CFBitVectorRef ArtemisAspectGetExclusionSet(ArtemisAspectRef);
CFBitVectorRef ArtemisAspectGetOneSet(ArtemisAspectRef);
ulong ArtemisAspectGetIndexFor(ArtemisAspectRef, CFClassRef);
ArtemisAspectRef ArtemisAspectAll(ArtemisAspectRef, ...);
ArtemisAspectRef ArtemisAspectExclude(ArtemisAspectRef, ...);
ArtemisAspectRef ArtemisAspectOne(ArtemisAspectRef, ...);


