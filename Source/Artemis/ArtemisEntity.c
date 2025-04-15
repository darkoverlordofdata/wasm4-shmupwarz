#include "artemis.h"
#include <stdlib.h>
/**
 * The entity class. Cannot be instantiated outside the framework, you must
 * create new entities using World.
 * 
 * @author Arni Arent
 * 
 */
typedef struct __ArtemisEntity {
    __CFObject                  obj;
    CFUuidRef                   uuid;
    CFStringRef                 name;
    ulong                       id;
    CFBitVectorRef              componentBits;
    CFBitVectorRef              systemBits;
    ArtemisWorldRef             world;
    ArtemisEntityManagerRef     entityManager;
    ArtemisComponentManagerRef  componentManager;
} __ArtemisEntity;

static __CFClass class = {
    .name = "ArtemisEntity",
    .size = sizeof(__ArtemisEntity),
    .ctor = ctor,
};
CFClassRef ArtemisEntity = &class;

static bool ctor(void *ptr, va_list args)
{
    ArtemisEntityRef this = ptr;
    this->world = va_arg(args, ArtemisWorldRef);
    this->id = va_arg(args, ulong);
    this->name = CFCreate(CFString, va_arg(args, char*));
    this->entityManager = ArtemisWorldGetEntityManager(this->world);
    this->componentManager = ArtemisWorldGetComponentManager(this->world);
    this->systemBits = CFCreate(CFBitVector, NULL);
    this->componentBits = CFCreate(CFBitVector, NULL);

    return true;
}

/**
 * The internal id for this entity within the framework. No other entity
 * will have the same ID, but ID's are however reused so another entity may
 * acquire this ID if the previous entity was deleted.
 * 
 * @return id of the entity.
 */
ulong ArtemisEntityGetId(ArtemisEntityRef this)
{
    return this->id;
}

/**
 * Returns a BitSet instance containing bits of the components the entity possesses.
 * @return
 */
CFBitVectorRef ArtemisEntityGetComponentBits(ArtemisEntityRef this)
{
    return this->componentBits;
}

/**
 * Returns a BitSet instance containing bits of the components the entity possesses.
 * @return
 */
CFBitVectorRef ArtemisEntityGetSystemBits(ArtemisEntityRef this)
{
    return this->systemBits;
}

/**
 * Make entity ready for re-use.
 * Will generate a new uuid for the entity.
 */
void ArtemisEntityReset(ArtemisEntityRef this)
{
    Clear(this->systemBits, false);
    Clear(this->componentBits, false);
    this->uuid = CFCreate(CFUuid);
}

CFObjectRef ArtemisEntityCreateComponent(ArtemisEntityRef this, CFClassRef cls, ...)
{
    ArtemisComponentManagerRef componentManager = ArtemisWorldGetComponentManager(this->world);
    CFObjectRef component = ArtemisComponentManagerCreate(componentManager, this, cls);
    // need a way to pass ... to component
    ArtemisComponentTypeFactoryRef tf = ArtemisComponentManagerGetTypeFactory(componentManager);
    ArtemisComponentTypeRef componentType = ArtemisComponentTypeFactoryGetTypeFor(tf, cls);
    Set(this->componentBits, (int)ArtemisComponentTypeGetIndex(componentType), true);
    return component;
}

/**
 * Faster adding of components into the entity. Not neccessery to use this, but
 * in some cases you might need the extra performance.
 * 
 * @param component the component to add
 * @param args of the component
 * 
 * @return this entity for chaining.
 */
ArtemisEntityRef ArtemisEntityAddComponent(ArtemisEntityRef this, CFObjectRef component, ...)
{
    ArtemisComponentTypeRef type = ArtemisEntityGetTypeFor(this, component->cls);
    ArtemisComponentManagerAddComponent(this->componentManager, this, type, component);
    return this;
}

ArtemisComponentTypeRef ArtemisEntityGetTypeFor(ArtemisEntityRef this, CFClassRef cls)
{
    ArtemisComponentManagerRef cm = ArtemisWorldGetComponentManager(this->world);
    ArtemisComponentTypeFactoryRef tf = ArtemisComponentManagerGetTypeFactory(cm);
    return ArtemisComponentTypeFactoryGetTypeFor(tf, cls);
}

ArtemisEntityRef ArtemisEntityRemoveComponentInstance(ArtemisEntityRef this, CFObjectRef component)
{
    ArtemisEntityRemoveComponent(this, ArtemisEntityGetTypeFor(this, component->cls));
    return this;
}

/**
 * Faster removal of components from a entity.
 * 
 * @param type to remove from this entity.
 * 
 * @return this entity for chaining.
 */
ArtemisEntityRef ArtemisEntityRemoveComponent(ArtemisEntityRef this, ArtemisComponentTypeRef type)
{
    ArtemisComponentManagerRemoveComponent(this->componentManager, this, type);
    return this;
}

/**
 * Remove component by its type.
 * @param type
 * 
 * @return this entity for chaining.
 */
ArtemisEntityRef ArtemisEntityRemoveComponentByType(ArtemisEntityRef this, CFClassRef cls)
{
    ArtemisEntityRemoveComponent(this, ArtemisEntityGetTypeFor(this, cls));
    return this;
}

/**
 * Checks if the entity has been added to the world and has not been deleted from it.
 * If the entity has been disabled this will still return true.
 * 
 * @return if it's active.
 */
bool ArtemisEntityIsActive(ArtemisEntityRef this)
{
    return ArtemisEntityManagerIsActive(this->entityManager, this->id);
}

/**
 * Will check if the entity is enabled in the world.
 * By default all entities that are added to world are enabled,
 * this will only return false if an entity has been explicitly disabled.
 * 
 * @return if it's enabled
 */
bool ArtemisEntityIsEnabled(ArtemisEntityRef this)
{
    return ArtemisEntityManagerIsEnaled(this->entityManager, this->id);
}

/**
 * This is the preferred method to use when retrieving a component from a
 * entity. It will provide good performance.
 * But the recommended way to retrieve components from an entity is using
 * the ComponentMapper.
 * 
 * @param type
 *            in order to retrieve the component fast you must provide a
 *            ComponentType instance for the expected component.
 * @return
 */
CFObjectRef ArtemisEntityGetComponent(ArtemisEntityRef this, ArtemisComponentTypeRef type)
{
    return ArtemisComponentManagerGetComponent(this->componentManager, this, type);
}

/**
 * Slower retrieval of components from this entity. Minimize usage of this,
 * but is fine to use e.g. when creating new entities and setting data in
 * components.
 * 
 * @param <T>
 *            the expected return component type.
 * @param type
 *            the expected return component type.
 * @return component that matches, or null if none is found.
 */
CFObjectRef ArtemisEntityGetComponentByType(ArtemisEntityRef this, CFClassRef cls)
{
    return ArtemisComponentManagerGetComponent(this->componentManager, this, ArtemisEntityGetTypeFor(this, cls));
}

/**
 * Returns a bag of all components this entity has.
 * You need to reset the bag yourself if you intend to fill it more than once.
 * 
 * @param fillBag the bag to put the components into.
 * @return the fillBag with the components in.
 */
CFBagRef ArtemisEntityGetComponents(ArtemisEntityRef this, CFBagRef fillBag)
{
    return ArtemisComponentManagerGetComponentsFor(this->componentManager, this, fillBag);
}

/**
 * Refresh all changes to components for this entity. After adding or
 * removing components, you must call this method. It will update all
 * relevant systems. It is typical to call this after adding components to a
 * newly created entity.
 */
void ArtemisEntityAddToWorld(ArtemisEntityRef this)
{
    ArtemisWorldAddEntity(this->world, this);
}

/**
 * This entity has changed, a component added or deleted.
 */
void ArtemisEntityChangeInWorld(ArtemisEntityRef this)
{
    ArtemisWorldChangedEntity(this->world, this);
}

/**
 * Delete this entity from the world.
 */
void ArtemisEntityDeleteFromWorld(ArtemisEntityRef this)
{
    ArtemisWorldDeleteEntity(this->world, this);
}

/**
 * (Re)enable the entity in the world, after it having being disabled.
 * Won't do anything unless it was already disabled.
 */
void ArtemisEntityEnable(ArtemisEntityRef this)
{
    ArtemisWorldEnable(this->world, this);
}

/**
 * Disable the entity from being processed. Won't delete it, it will
 * continue to exist but won't get processed.
 */
void ArtemisEntityDisable(ArtemisEntityRef this)
{
    ArtemisWorldDisable(this->world, this);
}

/**
 * Get the UUID for this entity.
 * This UUID is unique per entity (re-used entities get a new UUID).
 * @return uuid instance for this entity.
 */
CFStringRef ArtemisEntityGetUUID(ArtemisEntityRef this)
{
    return NewString(ToString(this->uuid));
}

/**
 * Returns the world this entity belongs to.
 * @return world of entity.
 */
ArtemisWorldRef ArtemisEntityGetWorld(ArtemisEntityRef this)
{
    return this->world;
}

