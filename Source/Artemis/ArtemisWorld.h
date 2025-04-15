#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
#include "ArtemisManager.h"
/**
 *  @class ArtemisWorld
 */
extern CFClassRef ArtemisWorld;

typedef struct __ArtemisWorld*              ArtemisWorldRef;
typedef struct __ArtemisEntityManager*      ArtemisEntityManagerRef;
typedef struct __ArtemisComponentManager*   ArtemisComponentManagerRef;
typedef struct __ArtemisEntity*             ArtemisEntityRef;
typedef struct __ArtemisEntitySystem*       ArtemisEntitySystemRef;
typedef struct __ArtemisComponentMapper*    ArtemisComponentMapperRef;

typedef void (^ArtemisPerform)(ArtemisManagerRef, ArtemisEntityRef);

ArtemisEntityManagerRef ArtemisWorldGetEntityManager(ArtemisWorldRef);
void ArtemisWorldInitialize(ArtemisWorldRef);
ArtemisComponentManagerRef ArtemisWorldGetComponentManager(ArtemisWorldRef);
CFObjectRef ArtemisWorldSetManager(ArtemisWorldRef, CFObjectRef);
CFObjectRef ArtemisWorldGetManager(ArtemisWorldRef, CFClassRef);
void ArtemisWorldDeleteManager(ArtemisWorldRef, CFObjectRef);
double ArtemisWorldGetDelta(ArtemisWorldRef);
void ArtemisWorldSetDelta(ArtemisWorldRef, double);
void ArtemisWorldAddEntity(ArtemisWorldRef, ArtemisEntityRef);
void ArtemisWorldChangedEntity(ArtemisWorldRef, ArtemisEntityRef);
void ArtemisWorldDeleteEntity(ArtemisWorldRef, ArtemisEntityRef);
void ArtemisWorldEnable(ArtemisWorldRef, ArtemisEntityRef);
void ArtemisWorldDisable(ArtemisWorldRef, ArtemisEntityRef);
ArtemisEntityRef ArtemisWorldCreateEntity(ArtemisWorldRef, CFStringRef);
ArtemisEntityRef ArtemisWorldGetEntity(ArtemisWorldRef, ulong);
CFBagRef ArtemisWorldGetSystems(ArtemisWorldRef);
ArtemisEntitySystemRef ArtemisWorldSetSystem(ArtemisWorldRef, ArtemisEntitySystemRef, bool);
void ArtemisWorldDeleteSystem(ArtemisWorldRef, ArtemisEntitySystemRef);
void ArtemisWorldNotifySystems(ArtemisWorldRef, ArtemisPerform, ArtemisEntityRef);
void ArtemisWorldNotifyManagers(ArtemisWorldRef, ArtemisPerform, ArtemisEntityRef);
ArtemisEntitySystemRef ArtemisWorldGetSystem(ArtemisWorldRef, CFClassRef);
void ArtemisWorldCheck(ArtemisWorldRef, CFBagRef, ArtemisPerform);
void ArtemisWorldProcess(ArtemisWorldRef);
ArtemisComponentMapperRef ArtemisWorldGetMapper(ArtemisWorldRef, CFClassRef);
void ArtemisWorldSetEntityTemplate(ArtemisWorldRef, CFStringRef, CFObjectRef);
ArtemisEntityRef ArtemisWorldCreateEntityFromTemplate(ArtemisWorldRef, CFStringRef, ...);


