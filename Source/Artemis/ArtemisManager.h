#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep0
/**
 *  @class ArtemisEntityManager
 */
extern CFClassRef ArtemisManager;
typedef struct __ArtemisWorld*          ArtemisWorldRef;

typedef struct __ArtemisManager {
    __CFObject                  obj;
    struct ArtemisManagerVtbl   const *vptr; 
    ArtemisWorldRef             world;

} __ArtemisManager;

typedef struct __ArtemisManager*        ArtemisManagerRef;
typedef struct __ArtemisEntity*         ArtemisEntityRef;

struct ArtemisManagerVtbl {
    void (*added)   (ArtemisManagerRef, ArtemisEntityRef);
    void (*changed) (ArtemisManagerRef, ArtemisEntityRef);
    void (*deleted) (ArtemisManagerRef, ArtemisEntityRef);
    void (*disabled)(ArtemisManagerRef, ArtemisEntityRef);
    void (*enabled) (ArtemisManagerRef, ArtemisEntityRef);
};

void ArtemisManagerSetWorld(ArtemisManagerRef, ArtemisWorldRef);

static inline void ArtemisManagerAdded(ArtemisManagerRef this, ArtemisEntityRef entity) 
{
    (*this->vptr->added)(this, entity);
}

static inline void ArtemisManagerChanged(ArtemisManagerRef this, ArtemisEntityRef entity)
{
    (*this->vptr->changed)(this, entity);
}

static inline void ArtemisManagerDisabled(ArtemisManagerRef this, ArtemisEntityRef entity)
{
    (*this->vptr->deleted)(this, entity);
}

static inline void ArtemisManagerEnabled(ArtemisManagerRef this, ArtemisEntityRef entity)
{
    (*this->vptr->disabled)(this, entity);
}

static inline void ArtemisManagerDeleted(ArtemisManagerRef this, ArtemisEntityRef entity)
{
    (*this->vptr->enabled)(this, entity);
}




