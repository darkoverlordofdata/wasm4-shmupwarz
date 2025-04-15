#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisEntity
 */
extern CFClassRef ArtemisEntity;

typedef struct __ArtemisEntity*             ArtemisEntityRef;
typedef struct __ArtemisWorld*              ArtemisWorldRef;
typedef struct __ArtemisEntityManager*      ArtemisEntityManagerRef;
typedef struct __ArtemisComponentManager*   ArtemisComponentManagerRef;
typedef struct __ArtemisComponentType*      ArtemisComponentTypeRef;

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
