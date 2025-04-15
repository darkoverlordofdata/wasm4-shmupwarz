#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisComponentMapper
 */
extern CFClassRef ArtemisComponentMapper;

typedef struct __ArtemisComponentMapper*    ArtemisComponentMapperRef;
typedef struct __ArtemisComponentType*      ArtemisComponentTypeRef;
typedef struct __ArtemisEntity*             ArtemisEntityRef;
typedef struct __ArtemisWorld*              ArtemisWorldRef;

CFObjectRef ArtemisComponentMapperGet(ArtemisComponentMapperRef, ArtemisEntityRef);
CFObjectRef ArtemisComponentMapperGetSafe(ArtemisComponentMapperRef, ArtemisEntityRef);
bool ArtemisComponentMapperHas(ArtemisComponentMapperRef, ArtemisEntityRef);
ArtemisComponentMapperRef ArtemisComponentMapperGetFor(CFClassRef, ArtemisWorldRef);

