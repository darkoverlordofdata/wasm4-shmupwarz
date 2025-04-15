#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep0
#include "ArtemisManager.h"
#include "ArtemisIdentifierPool.h"
#include "ArtemisEntity.h"
/**
 *  @class ArtemisEntityManager
 */
extern CFClassRef ArtemisEntityManager;

typedef struct __ArtemisEntityManager*  ArtemisEntityManagerRef;
typedef struct __ArtemisWorld*          ArtemisWorldRef;
typedef struct __ArtemisEntity*         ArtemisEntityRef;

typedef struct __ArtemisEntityManager {
    __ArtemisManager            base;
    CFBagRef                    entities;
    CFBitVectorRef              disabled;
    ulong                       active;
    ulong                       added;
    ulong                       created;
    ulong                       deleted;
    ArtemisIdentifierPoolRef    identifierPool;

} __ArtemisEntityManager;


ArtemisEntityRef ArtemisEntityManagerCreateEntityInstance(ArtemisEntityManagerRef, CFStringRef);
bool ArtemisEntityManagerIsActive(ArtemisEntityManagerRef, ulong);
bool ArtemisEntityManagerIsEnaled(ArtemisEntityManagerRef, ulong);
ArtemisEntityRef ArtemisEntityManageGetEntity(ArtemisEntityManagerRef, ulong);
ulong ArtemisEntityManageGetActiveEntityCount(ArtemisEntityManagerRef);
ulong ArtemisEntityManageGetTotalCreated(ArtemisEntityManagerRef);
ulong ArtemisEntityManageGetTotalAdded(ArtemisEntityManagerRef);
ulong ArtemisEntityManageGetTotalDeleted(ArtemisEntityManagerRef);
void ArtemisEntityManageSetWorld(ArtemisEntityManagerRef, ArtemisWorldRef);



static inline void ArtemisEntityManagerAdded(ArtemisManagerRef ptr, ArtemisEntityRef e)
{ 
    ArtemisEntityManagerRef this = (ArtemisEntityManagerRef)ptr;
    this->active++;
    this->added++;
    CFBagSet(this->entities, (size_t)ArtemisEntityGetId(e), e);
}

static inline void ArtemisEntityManagerChanged(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    (void*)ptr;
    (void*)e;
}

static inline void ArtemisEntityManagerEnabled(ArtemisManagerRef ptr, ArtemisEntityRef e)
{ 
    ArtemisEntityManagerRef this = (ArtemisEntityManagerRef)ptr;
    Set(this->disabled, (int)ArtemisEntityGetId(e), false);
}

static inline void ArtemisEntityManagerDisabled(ArtemisManagerRef ptr, ArtemisEntityRef e)
{ 
    ArtemisEntityManagerRef this = (ArtemisEntityManagerRef)ptr;
    Set(this->disabled, (int)ArtemisEntityGetId(e), true);
}

static inline void ArtemisEntityManagerDeleted(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    ArtemisEntityManagerRef this = (ArtemisEntityManagerRef)ptr;
    CFBagSet(this->entities, (size_t)ArtemisEntityGetId(e), NULL);
    Set(this->disabled, (int)ArtemisEntityGetId(e), false);
    ArtemisIdentifierPoolCheckIn(this->identifierPool, (size_t)ArtemisEntityGetId(e));
    this->active--;
    this->deleted++;
}
