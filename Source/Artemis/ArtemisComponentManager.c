#include "artemis.h"

static __CFClass class = {
    .name = "ArtemisComponentManager",
    .size = sizeof(__ArtemisComponentManager),
    .ctor = ctor,
};
CFClassRef ArtemisComponentManager = &class;

/**
*   Component Manager Class
*/

static bool ctor(void *ptr, va_list args)
{
    (void*)args;
    ArtemisComponentManagerRef this = ptr;
    this->componentsByType = CFCreate(CFArray, NULL);
    this->pooledComponents = CFCreate(ArtemisComponentPool);
    this->deleted = CFCreate(CFArray, NULL);
    this->typeFactory = CFCreate(ArtemisComponentTypeFactory);

    static struct ArtemisManagerVtbl const vtbl = { &ArtemisComponentManagerAdded, 
                                                    &ArtemisComponentManagerChanged,
                                                    &ArtemisComponentManagerDeleted,
                                                    &ArtemisComponentManagerDisabled,
                                                    &ArtemisComponentManagerEnabled };
    this->base.vptr = &vtbl;               
    return true;
}

void ArtemisComponentManagerSetWorld(
    ArtemisComponentManagerRef this, 
    ArtemisWorldRef world)
{
    this->base.world = world;
}


void ArtemisComponentManagerInitialize(
    ArtemisComponentManagerRef this)
{
    (void*)this;
}

CFObjectRef ArtemisComponentManagerCreate(
    ArtemisComponentManagerRef this, 
    ArtemisEntityRef owner, 
    CFClassRef componentClass)
{   
    ArtemisComponentTypeRef type = ArtemisComponentTypeFactoryGetTypeFor(this->typeFactory, componentClass);
    CFObjectRef component;

    switch(ArtemisComponentTypeGetTaxonomy(type))
    {
        case ArtemisTaxonomy_BASIC:
            component = ArtemisComponentManagerNewInstance(this, componentClass, false);
            break;
        case ArtemisTaxonomy_POOLED:
            component = ArtemisComponentManagerNewInstance(this, componentClass, false);
            break;
        default:
            component = NULL;
            break;
    }
    ArtemisComponentManagerAddComponent(this, owner, type, component);
    return component;
}

CFObjectRef ArtemisComponentManagerNewInstance(
    ArtemisComponentManagerRef this, 
    CFClassRef cls, 
    bool constructorHasWorldParameter)
{
    if (constructorHasWorldParameter) {
        return CFCreate(cls, this->base.world);
    } else {
        return CFCreate(cls);
    }
}

/**
 * Removes all components from the entity associated in this manager.
 *
 * @param e
 *          the entity to remove components from
 */
void ArtemisComponentManagerRemoveComponentsOfEntity(
    ArtemisComponentManagerRef this, 
    ArtemisEntityRef e)
{
    CFBitVectorRef componentBits = ArtemisEntityGetComponentBits(e);
    for (int i = 0; i<Size(componentBits); i++) {
        if (Get(componentBits, i)) {
            switch (ArtemisComponentTypeFactoryGetTaxonomy(this->typeFactory, (ulong)i)) {
                case ArtemisTaxonomy_BASIC:
                    CFBagSet(this->componentsByType, ArtemisEntityGetId(e), NULL);
                    break;

                case ArtemisTaxonomy_POOLED:
                    CFBagSet(this->componentsByType, ArtemisEntityGetId(e), NULL);
                    break;
        
                default:
                    break;
            }
        }
    }
}

/**
 * Adds the component of the given type to the entity.
 * <p>
 * Only one component of given type can be associated with a entity at the
 * same time.
 * </p>
 *
 * @param e
 *            the entity to add to
 * @param type
 *            the type of component being added
 * @param component
 *            the component to add
 */
void ArtemisComponentManagerAddComponent(
    ArtemisComponentManagerRef this, 
    ArtemisEntityRef e, 
    ArtemisComponentTypeRef type, 
    CFObjectRef component)
{
    CFBagRef components = CFBagGet(this->componentsByType, ArtemisComponentTypeGetIndex(type));
    if (components == NULL) {
        components = CFCreate(CFArray, NULL);
        CFBagSet(this->componentsByType, ArtemisComponentTypeGetIndex(type), components);
    }
    CFBagSet(components, ArtemisEntityGetId(e), component);
    Set(ArtemisEntityGetComponentBits(e), (int)ArtemisComponentTypeGetIndex(type), true);
}

/**
 * Removes the component of given type from the entity.
 *
 * @param e
 *            the entity to remove from
 * @param type
 *            the type of component being removed
 */
void ArtemisComponentManagerRemoveComponent(
    ArtemisComponentManagerRef this, 
    ArtemisEntityRef e, 
    ArtemisComponentTypeRef type)
{
    int index = (int)ArtemisComponentTypeGetIndex(type);
    switch (ArtemisComponentTypeGetTaxonomy(type)) {
        case ArtemisTaxonomy_BASIC:
            CFBagSet(this->componentsByType, ArtemisEntityGetId(e), NULL);
            Set(ArtemisEntityGetComponentBits(e), index, false);
            break;

        case ArtemisTaxonomy_POOLED:
            CFBagSet(this->componentsByType, ArtemisEntityGetId(e), NULL);
            Set(ArtemisEntityGetComponentBits(e), index, false);
            break;
 
        default:
            break;
    }

}

/**
 * Get all components from all entities for a given type.
 *
 * @param type
 *            the type of components to get
 * @return a bag containing all components of the given type
 */
CFBagRef ArtemisComponentManagerGetComponentsByType(
    ArtemisComponentManagerRef this, 
    ArtemisComponentTypeRef type)
{
    CFBagRef components = CFBagGet(this->componentsByType, ArtemisComponentTypeGetIndex(type));
    if (components == NULL) {
        components = CFCreate(CFArray, NULL);
        CFBagSet(this->componentsByType, ArtemisComponentTypeGetIndex(type), components);   
    }
    return components;
}

/**
 * Get a component of an entity.
 *
 * @param e
 *            the entity associated with the component
 * @param type
 *            the type of component to get
 * @return the component of given type
 */
CFObjectRef ArtemisComponentManagerGetComponent(
    ArtemisComponentManagerRef this, 
    ArtemisEntityRef e, 
    ArtemisComponentTypeRef type)
{
    CFBagRef components = CFBagGet(this->componentsByType, ArtemisComponentTypeGetIndex(type));
    if (components != NULL) {
        return CFBagGet(components, ArtemisEntityGetId(e));
    }
    return NULL;
}

/**
 * Get all component associated with an entity.
 *
 * @param e
 *            the entity to get components from
 * @param fillBag
 *            a bag to be filled with components
 * @return the {@code fillBag}, filled with the entities components
 */
CFBagRef ArtemisComponentManagerGetComponentsFor(
    ArtemisComponentManagerRef this, 
    ArtemisEntityRef e, 
    CFBagRef fillBag)
{
    CFBitVectorRef componentBits = ArtemisEntityGetComponentBits(e);
    for (int i = 0; i<Size(componentBits); i++) {
        CFBagRef c = CFBagGet(this->componentsByType, (size_t)i);
        CFBagAdd(fillBag, CFBagGet(c, ArtemisEntityGetId(e)));
    } 
    return fillBag;
}


void ArtemisComponentManagerClean(
    ArtemisComponentManagerRef this)
{
    if (CFBagSize(this->deleted) > 0) {
        for (ulong i=0; CFBagSize(this->deleted) > i; i++) {
            ArtemisComponentManagerRemoveComponentsOfEntity(this, CFBagGet(this->deleted, i));
        }
    }
}

ArtemisComponentTypeFactoryRef ArtemisComponentManagerGetTypeFactory(
    ArtemisComponentManagerRef this)
{
    return this->typeFactory;
}

