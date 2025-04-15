#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
#include "ArtemisTaxonomy.h"                  // IWYU pragma: keep
/**
 *  @class ArtemisComponentType
 */
extern CFClassRef ArtemisComponentType;

typedef struct __ArtemisComponentType*      ArtemisComponentTypeRef;
typedef struct __ArtemisComponentManager*   ArtemisComponentManagerRef;

extern ulong ArtemisComponentTypeIndex;

CFStringRef ArtemisComponentTypeGetName(ArtemisComponentTypeRef);
ulong ArtemisComponentTypeGetIndex(ArtemisComponentTypeRef);
ArtemisTaxonomy ArtemisComponentTypeGetTaxonomy(ArtemisComponentTypeRef);
