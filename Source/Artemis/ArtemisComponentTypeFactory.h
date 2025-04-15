#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
#include "ArtemisTaxonomy.h"                  // IWYU pragma: keep
/**
 *  @class ArtemisComponentTypeFactory
 */
extern CFClassRef ArtemisComponentTypeFactory;

typedef struct __ArtemisComponentTypeFactory*   ArtemisComponentTypeFactoryRef;
typedef struct __ArtemisComponentType*          ArtemisComponentTypeRef;

extern ArtemisComponentTypeFactoryRef ArtemisAspectTypeFactory;

ArtemisComponentTypeRef ArtemisComponentTypeFactoryGetTypeFor(ArtemisComponentTypeFactoryRef, CFClassRef);
ulong ArtemisComponentTypeFactoryGetIndexFor(ArtemisComponentTypeFactoryRef, CFClassRef);
ArtemisTaxonomy ArtemisComponentTypeFactoryGetTaxonomy(ArtemisComponentTypeFactoryRef, ulong);
