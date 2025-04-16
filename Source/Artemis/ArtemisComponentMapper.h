#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisComponentMapper
 */
extern CFClassRef ArtemisComponentMapper;
typedef struct __ArtemisWorld*              ArtemisWorldRef;
typedef struct __ArtemisComponentType*      ArtemisComponentTypeRef;

typedef struct __ArtemisComponentMapper {
    __CFObject                  obj;
    ArtemisWorldRef             world;
    ArtemisComponentTypeRef     type;
    CFClassRef                  classType;
    CFBagRef                    components;
} __ArtemisComponentMapper;

typedef struct __ArtemisComponentMapper*    ArtemisComponentMapperRef;
typedef struct __ArtemisEntity*             ArtemisEntityRef;

ArtemisComponentMapperRef method Ctor(ArtemisComponentMapperRef, CFClassRef, ArtemisWorldRef);
CFObjectRef ArtemisComponentMapperGet(ArtemisComponentMapperRef, ArtemisEntityRef);
CFObjectRef ArtemisComponentMapperGetSafe(ArtemisComponentMapperRef, ArtemisEntityRef);
bool ArtemisComponentMapperHas(ArtemisComponentMapperRef, ArtemisEntityRef);
ArtemisComponentMapperRef ArtemisComponentMapperGetFor(CFClassRef, ArtemisWorldRef);

static inline ArtemisComponentMapperRef NewArtemisComponentMapper(CFClassRef cls, ArtemisWorldRef world)
{
    return Ctor((ArtemisComponentMapperRef)CFCreate(ArtemisComponentMapper), cls, world);
}

