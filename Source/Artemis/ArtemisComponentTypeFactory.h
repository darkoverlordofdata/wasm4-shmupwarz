#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
#include "ArtemisTaxonomy.h"                  // IWYU pragma: keep
/**
 *  @class ArtemisComponentTypeFactory
 */
extern CFClassRef ArtemisComponentTypeFactory;

typedef struct __ArtemisComponentTypeFactory {
    __CFObject  obj;
    /**
     * Contains all generated component types, newly generated component types
     * will be stored here.
     */
    CFMapRef    componentTypes;
    /** Amount of generated component types. */
    ulong       componentTypeCount;
    /** Index of this component type in componentTypes. */
    CFBagRef    types;

} __ArtemisComponentTypeFactory;

typedef struct __ArtemisComponentTypeFactory*   ArtemisComponentTypeFactoryRef;
typedef struct __ArtemisComponentType*          ArtemisComponentTypeRef;

extern ArtemisComponentTypeFactoryRef ArtemisAspectTypeFactory;

ArtemisComponentTypeFactoryRef method Ctor(ArtemisComponentTypeFactoryRef);
ArtemisComponentTypeRef ArtemisComponentTypeFactoryGetTypeFor(ArtemisComponentTypeFactoryRef, CFClassRef);
ulong ArtemisComponentTypeFactoryGetIndexFor(ArtemisComponentTypeFactoryRef, CFClassRef);
ArtemisTaxonomy ArtemisComponentTypeFactoryGetTaxonomy(ArtemisComponentTypeFactoryRef, ulong);

static inline ArtemisComponentTypeFactoryRef NewArtemisComponentTypeFactory()
{
    return Ctor((ArtemisComponentTypeFactoryRef)CFCreate(ArtemisComponentTypeFactory));
}
