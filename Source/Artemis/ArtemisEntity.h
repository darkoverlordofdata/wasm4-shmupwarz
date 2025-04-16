#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisEntity
 */
extern CFClassRef ArtemisEntity;
typedef struct __ArtemisWorld*              ArtemisWorldRef;
typedef struct __ArtemisEntityManager*      ArtemisEntityManagerRef;
typedef struct __ArtemisComponentManager*   ArtemisComponentManagerRef;

typedef struct __ArtemisEntity {
    __CFObject                  obj;
    CFUuidRef                   uuid;
    CFStringRef                 name;
    ulong                       id;
    CFBitVectorRef              componentBits;
    CFBitVectorRef              systemBits;
    ArtemisWorldRef             world;
    ArtemisEntityManagerRef     entityManager;
    ArtemisComponentManagerRef  componentManager;
} __ArtemisEntity;

typedef struct __ArtemisEntity*             ArtemisEntityRef;
typedef struct __ArtemisComponentType*      ArtemisComponentTypeRef;

ArtemisEntityRef method Ctor(ArtemisEntityRef, ArtemisWorldRef, ulong, char*);
ulong ArtemisEntityGetId(ArtemisEntityRef);
CFBitVectorRef ArtemisEntityGetComponentBits(ArtemisEntityRef);
CFBitVectorRef ArtemisEntityGetSystemBits(ArtemisEntityRef);
void ArtemisEntityReset(ArtemisEntityRef);
CFObjectRef ArtemisEntityCreateComponent(ArtemisEntityRef, CFClassRef, ...);
ArtemisEntityRef ArtemisEntityAddComponent(ArtemisEntityRef, CFObjectRef, ...);
ArtemisComponentTypeRef ArtemisEntityGetTypeFor(ArtemisEntityRef, CFClassRef);
ArtemisEntityRef ArtemisEntityRemoveComponentInstance(ArtemisEntityRef, CFObjectRef);
ArtemisEntityRef ArtemisEntityRemoveComponent(ArtemisEntityRef, ArtemisComponentTypeRef);
ArtemisEntityRef ArtemisEntityRemoveComponentByType(ArtemisEntityRef, CFClassRef);
bool ArtemisEntityIsActive(ArtemisEntityRef);
bool ArtemisEntityIsEnabled(ArtemisEntityRef);
CFObjectRef ArtemisEntityGetComponent(ArtemisEntityRef, ArtemisComponentTypeRef);
CFObjectRef ArtemisEntityGetComponentByType(ArtemisEntityRef, CFClassRef);
CFBagRef ArtemisEntityGetComponents(ArtemisEntityRef, CFBagRef);
void ArtemisEntityAddToWorld(ArtemisEntityRef);
void ArtemisEntityChangeInWorld(ArtemisEntityRef);
void ArtemisEntityDeleteFromWorld(ArtemisEntityRef);
void ArtemisEntityEnable(ArtemisEntityRef);
void ArtemisEntityDisable(ArtemisEntityRef);
CFStringRef ArtemisEntityGetUUID(ArtemisEntityRef);
ArtemisWorldRef ArtemisEntityGetWorld(ArtemisEntityRef);
CFStringRef ArtemisWorldRandomUUID();

static inline ArtemisEntityRef NewArtemisEntity(ArtemisWorldRef world, ulong id, char* name)
{
    return Ctor((ArtemisEntityRef)CFCreate(ArtemisEntity), world, id, name);
}
