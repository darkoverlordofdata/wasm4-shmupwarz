#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
#include "ArtemisTaxonomy.h"                  // IWYU pragma: keep
/**
 *  @class ArtemisComponentType
 */
extern CFClassRef ArtemisComponentType;
typedef struct __ArtemisComponentManager*   ArtemisComponentManagerRef;

typedef struct __ArtemisComponentType {
    __CFObject                  obj;
    ArtemisComponentManagerRef  componentManager;
    ulong                       index;
    CFClassRef                  type;   
    ArtemisTaxonomy             taxonomy;

} __ArtemisComponentType;

typedef struct __ArtemisComponentType*      ArtemisComponentTypeRef;

extern ulong ArtemisComponentTypeIndex;

ArtemisComponentTypeRef method Ctor(ArtemisComponentTypeRef, CFClassRef, ulong);
CFStringRef ArtemisComponentTypeGetName(ArtemisComponentTypeRef);
ulong ArtemisComponentTypeGetIndex(ArtemisComponentTypeRef);
ArtemisTaxonomy ArtemisComponentTypeGetTaxonomy(ArtemisComponentTypeRef);

static inline ArtemisComponentTypeRef NewArtemisComponentType(CFClassRef cls, ulong index)
{
    return Ctor((ArtemisComponentTypeRef)CFCreate(ArtemisComponentType), cls, index);
}