#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
#include "ArtemisManager.h"
/**
* @class ArtemisComponentManager
*/
extern CFClassRef ArtemisComponentManager;
typedef struct __ArtemisWorld*                  ArtemisWorldRef;
typedef struct __ArtemisComponentPool*          ArtemisComponentPoolRef;
typedef struct __ArtemisComponentTypeFactory*   ArtemisComponentTypeFactoryRef;

typedef struct __ArtemisComponentManager {
    __ArtemisManager                    base;
    CFBagRef                            componentsByType;
    ArtemisComponentPoolRef             pooledComponents;
    CFBagRef                            deleted;
    ArtemisComponentTypeFactoryRef      typeFactory;
} __ArtemisComponentManager;

typedef struct __ArtemisComponentManager*       ArtemisComponentManagerRef;
typedef struct __ArtemisComponentTypeFactory*   ArtemisComponentTypeFactoryRef;
typedef struct __ArtemisComponentPool*          ArtemisComponentPoolRef;
typedef struct __ArtemisEntity*                 ArtemisEntityRef;
typedef struct __ArtemisComponentType*          ArtemisComponentTypeRef;
typedef struct __ArtemisWorld*                  ArtemisWorldRef;

ArtemisComponentManagerRef method Ctor(ArtemisComponentManagerRef);
void ArtemisComponentManagerInitialize(ArtemisComponentManagerRef);
CFObjectRef ArtemisComponentManagerCreate(ArtemisComponentManagerRef, ArtemisEntityRef, CFClassRef);
CFObjectRef ArtemisComponentManagerNewInstance(ArtemisComponentManagerRef, CFClassRef, bool);
void ArtemisComponentManagerAddComponent(ArtemisComponentManagerRef, ArtemisEntityRef, ArtemisComponentTypeRef, CFObjectRef);
void ArtemisComponentManagerRemoveComponent(ArtemisComponentManagerRef, ArtemisEntityRef, ArtemisComponentTypeRef);
void ArtemisComponentManagerRemoveComponentsOfEntity(ArtemisComponentManagerRef, ArtemisEntityRef);
CFBagRef ArtemisComponentManagerGetComponentsByType(ArtemisComponentManagerRef, ArtemisComponentTypeRef);
CFObjectRef ArtemisComponentManagerGetComponent(ArtemisComponentManagerRef, ArtemisEntityRef, ArtemisComponentTypeRef);
CFBagRef ArtemisComponentManagerGetComponentsFor(ArtemisComponentManagerRef, ArtemisEntityRef, CFBagRef);
void ArtemisComponentManagerClean(ArtemisComponentManagerRef);
ArtemisComponentTypeFactoryRef ArtemisComponentManagerGetTypeFactory(ArtemisComponentManagerRef);
void ArtemisComponentManagerSetWorld(ArtemisComponentManagerRef, ArtemisWorldRef);

/**
 * NewArtemisComponentManager
 * 
 * alloc+ctor
 */
static inline ArtemisComponentManagerRef NewArtemisComponentManager()
{
    return Ctor((ArtemisComponentManagerRef)CFCreate(ArtemisComponentManager));
}

/**
 * virtual functions
 */
 static inline void ArtemisComponentManagerAdded(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    (ArtemisManagerRef)ptr;
    (ArtemisEntityRef)e;
}

static inline void ArtemisComponentManagerChanged(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    (ArtemisManagerRef)ptr;
    (ArtemisEntityRef)e;
}
static inline void ArtemisComponentManagerEnabled(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    (ArtemisManagerRef)ptr;
    (ArtemisEntityRef)e;
}
static inline void ArtemisComponentManagerDisabled(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    (ArtemisManagerRef)ptr;
    (ArtemisEntityRef)e;
}

static inline void ArtemisComponentManagerDeleted(ArtemisManagerRef ptr, ArtemisEntityRef e)
{
    ArtemisComponentManagerRef this = (ArtemisComponentManagerRef)ptr;
    CFBagAdd(this->deleted, e);
}
