#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisEntitySystem
 */
extern CFClassRef ArtemisEntitySystem;
typedef struct __ArtemisWorld*          ArtemisWorldRef;
typedef struct __ArtemisAspect*         ArtemisAspectRef;

typedef struct __ArtemisEntitySystem {
    __CFObject          obj;
    ulong               systemIndex;  
    ArtemisWorldRef     world;
    CFBagRef            actives;
    ArtemisAspectRef    aspect;
    CFBitVectorRef      allSet;
    CFBitVectorRef      exclusionSet;
    CFBitVectorRef      oneSet;
    bool                passive;
    bool                dummy;
} __ArtemisEntitySystem;

typedef struct __ArtemisEntitySystem*   ArtemisEntitySystemRef;
typedef struct __ArtemisEntity*         ArtemisEntityRef;

ArtemisEntitySystemRef method Ctor(ArtemisEntitySystemRef, ArtemisAspectRef);
void ArtemisEntitySystemBegin(ArtemisEntitySystemRef);
void ArtemisEntitySystemProcess(ArtemisEntitySystemRef);
void ArtemisEntitySystemEnd(ArtemisEntitySystemRef);
void ArtemisEntitySystemProcessEntities(ArtemisEntitySystemRef, CFBagRef);
bool ArtemisEntitySystemCheckProcessing(ArtemisEntitySystemRef);
void ArtemisEntitySystemInitialize(ArtemisEntitySystemRef);
void ArtemisEntitySystemInserted(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemRemoved(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemCheck(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemRemoveFromSystem(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemInsertToSystem(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemAdded(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemChanged(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemDeleted(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemDisabled(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemEnabled(ArtemisEntitySystemRef, ArtemisEntityRef);
void ArtemisEntitySystemSetWorld(ArtemisEntitySystemRef, ArtemisWorldRef);
bool ArtemisEntitySystemIsPassive(ArtemisEntitySystemRef);
void ArtemisEntitySystemSetPassive(ArtemisEntitySystemRef, bool);
CFBagRef ArtemisEntitySystemGetActive(ArtemisEntitySystemRef);

static inline ArtemisEntitySystemRef NewArtemisEntitySystem(ArtemisAspectRef aspect)
{
    return Ctor((ArtemisEntitySystemRef)CFCreate(ArtemisEntitySystem), aspect);
}

