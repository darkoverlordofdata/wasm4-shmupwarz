/**
 * Contains all generated component types, newly generated component types
 * will be stored here.
 */
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisComponentTypeFactory);

ArtemisComponentTypeFactoryRef method Ctor(ArtemisComponentTypeFactoryRef this)
{
    this->componentTypes = CFCreate(CFMap, nullptr);
    this->types = CFCreate(CFArray, nullptr);
    this->componentTypeCount = 0;
    ArtemisAspectTypeFactory = this;

    return this;
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
    if (type == nullptr) {
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

