#include "../artemis.h"
#include "ArtemisComponentManager.h"
#include "ArtemisComponentType.h"
/**
 * Contains all generated component types, newly generated component types
 * will be stored here.
 */
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

static struct __CFClass class = {
    .name = "ArtemisComponentTypeFactory",
    .size = sizeof(struct __ArtemisComponentTypeFactory),
    .ctor = ctor,
};
CFClassRef ArtemisComponentTypeFactory = &class;

static bool ctor(void *ptr, va_list args)
{
    (void*)args;
    ArtemisComponentTypeFactoryRef this = ptr;

    this->componentTypes = CFCreate(CFMap, NULL);
    this->types = CFCreate(CFArray, NULL);
    this->componentTypeCount = 0;
    ArtemisAspectTypeFactory = this;

    return true;
}

/**
 * Gets the component type for the given component class.
 * <p>
 * If no component type exists yet, a new one will be created and stored
 * for later retrieval.
 * </p>
 *
 * @param c
 *			the component's class to get the type for
 *
 * @return the component's {@link ComponentType}
 */
ArtemisComponentTypeRef ArtemisComponentTypeFactoryGetTypeFor(ArtemisComponentTypeFactoryRef this, CFClassRef cls)
{
    ArtemisComponentTypeRef type = CFMapGet(this->componentTypes, CFCreate(CFString, cls->name));
    if (type == NULL) {
        ulong index = this->componentTypeCount++;
        type = CFCreate(ArtemisComponentType, cls , index);
        CFMapSet(this->componentTypes, CFCreate(CFString, cls->name), type);
        CFBagSet(this->types, index, type);
    }
    return type;
}

/**
 * Get the index of the component type of given component class.
 *
 * @param c
 *			the component class to get the type index for
 *
 * @return the component type's index
 */
ulong ArtemisComponentTypeFactoryGetIndexFor(ArtemisComponentTypeFactoryRef this, CFClassRef cls)
{
    return ArtemisComponentTypeGetIndex(ArtemisComponentTypeFactoryGetTypeFor(this, cls));
}

ArtemisTaxonomy ArtemisComponentTypeFactoryGetTaxonomy(ArtemisComponentTypeFactoryRef this, ulong index)
{
    return ArtemisComponentTypeGetTaxonomy(CFBagGet(this->types, index));
}

