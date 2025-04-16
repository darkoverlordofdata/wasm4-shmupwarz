// #include "ArtemisComponentManager.h"
// #include "ArtemisEntitySystem.h"
// #include "ArtemisWorld.h"
/**
* The primary instance for the framework. It contains all the managers.
* 
* You must use this to create, delete and retrieve entities.
* 
* It is also important to set the delta each game loop iteration, and initialize before game loop.
* 
* @author Arni Arent
* 
*/
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisWorld);

ArtemisWorldRef method Ctor(ArtemisWorldRef this)
{
    (ArtemisWorldRef)this;

    this->managers = CFCreate(CFMap, nullptr);
    this->managersBag = CFCreate(CFBag, 64);
    this->systems = CFCreate(CFMap, nullptr);
    this->systemsBag = CFCreate(CFBag, 64);
    this->added = CFCreate(CFBag, 64);
    this->changed = CFCreate(CFBag, 64);
    this->deleted = CFCreate(CFBag, 64);
    this->enable = CFCreate(CFBag, 64);
    this->disable = CFCreate(CFBag, 64);

    this->cm = CFCreate(ArtemisComponentManager);
    ArtemisWorldSetManager(this, (CFObjectRef)this->cm);

    this->em = CFCreate(ArtemisEntityManager);
    ArtemisWorldSetManager(this, (CFObjectRef)this->em);

    return this;
}

/**
 * Makes sure all managers systems are initialized in the order they were added.
 */
void ArtemisWorldInitialize(
    ArtemisWorldRef this)
{
    for (ulong i=0; i<CFBagSize(this->managersBag); i++) {
        ArtemisComponentManagerInitialize(CFBagGet(this->managersBag, i));
    }

    for (ulong i=0; i<CFBagSize(this->systemsBag); i++) {
        ArtemisEntitySystemInitialize(CFBagGet(this->systemsBag, i));
    }
}

/**
 * Returns a manager that takes care of all the entities in the world.
 * entities of this world.
 * 
 * @return entity manager.
 */
ArtemisEntityManagerRef ArtemisWorldGetEntityManager(
    ArtemisWorldRef this)
{
    return this->em;
}

/**
 * Returns a manager that takes care of all the components in the world.
 * 
 * @return component manager.
 */
ArtemisComponentManagerRef ArtemisWorldGetComponentManager(
    ArtemisWorldRef this)
{
    return this->cm;
}

/**
 * Add a manager into this world. It can be retrieved later.
 * World will notify this manager of changes to entity.
 * 
 * @param manager to be added
 */
CFObjectRef ArtemisWorldSetManager(
    ArtemisWorldRef this, 
    CFObjectRef manager)
{
    CFMapSet(this->managers, NewString((char*)manager->cls->name), manager);
    CFBagAdd(this->managersBag, manager);
    ArtemisManagerSetWorld((ArtemisManagerRef)manager, this);
    return manager;
}

/**
 * Returns a manager of the specified type.
 * 
 * @param <T>
 * @param managerType
 *            class type of the manager
 * @return the manager
 */
CFObjectRef ArtemisWorldGetManager(
    ArtemisWorldRef this, 
    CFClassRef cls)
{
    return CFMapGet(this->managers, NewString((char*)cls->name));
}

/**
 * Deletes the manager from this world.
 * @param manager to delete.
 */
void ArtemisWorldDeleteManager(
    ArtemisWorldRef this, 
    CFObjectRef manager)
{
    CFMapSet(this->managers, NewString((char*)manager->cls->name), nullptr);
    CFBagRemove(this->managersBag, manager);
}

/**
 * Time since last game loop.
 * 
 * @return delta time since last game loop.
 */
double ArtemisWorldGetDelta(
    ArtemisWorldRef this)
{
    return this->delta;
}

/**
 * You must specify the delta for the game here.
 * 
 * @param delta time since last game loop.
 */
void ArtemisWorldSetDelta(
    ArtemisWorldRef this, 
    double delta)
{
    this->delta = (float)delta;
}

/**
 * Adds a entity to this world.
 * 
 * @param e entity
 */
void ArtemisWorldAddEntity(
    ArtemisWorldRef this, 
    ArtemisEntityRef e)
{
    CFBagAdd(this->added, e);
}

/**
 * Ensure all systems are notified of changes to this entity.
 * If you're adding a component to an entity after it's been
 * added to the world, then you need to invoke this method.
 * 
 * @param e entity
 */
void ArtemisWorldChangedEntity(
    ArtemisWorldRef this, 
    ArtemisEntityRef e)
{
    CFBagAdd(this->changed, e);
}

/**
 * Delete the entity from the world.
 * 
 * @param e entity
 */
void ArtemisWorldDeleteEntity(
    ArtemisWorldRef this, 
    ArtemisEntityRef e)
{
    if (!CFBagContains(this->deleted, e))
        CFBagAdd(this->deleted, e);
}

/**
 * (Re)enable the entity in the world, after it having being disabled.
 * Won't do anything unless it was already disabled.
 */
void ArtemisWorldEnable(
    ArtemisWorldRef this, 
    ArtemisEntityRef e)
{
    CFBagAdd(this->enable, e);
}

/**
 * Disable the entity from being processed. Won't delete it, it will
 * continue to exist but won't get processed.
 */
void ArtemisWorldDisable(
    ArtemisWorldRef this, 
    ArtemisEntityRef e)
{
    CFBagAdd(this->disable, e);
}

/**
 * Create and return a new or reused entity instance.
 * Will NOT add the entity to the world, use World.addEntity(Entity) for that.
 *
 * @param name optional name for debugging
 * @return entity
 */
ArtemisEntityRef ArtemisWorldCreateEntity(
    ArtemisWorldRef this, 
    CFStringRef name)
{
    return ArtemisEntityManagerCreateEntityInstance(this->em, name);
}

/**
 * Get a entity having the specified id.
 * 
 * @param entityId
 * @return entity
 */
ArtemisEntityRef ArtemisWorldGetEntity(
    ArtemisWorldRef this, 
    ulong id)
{
    return ArtemisEntityManageGetEntity(this->em, id);
}

/**
 * Gives you all the systems in this world for possible iteration.
 * 
 * @return all entity systems in world.
 */
CFBagRef ArtemisWorldGetSystems(
    ArtemisWorldRef this)
{
    return this->systemsBag;
}

/**
 * Will add a system to this world.
 *  
 * @param system the system to add.
 * @param passive wether or not this system will be processed by World.process()
 * @return the added system.
 */
ArtemisEntitySystemRef ArtemisWorldSetSystem(
    ArtemisWorldRef this, 
    ArtemisEntitySystemRef system, 
    bool passive)
{
    CFObjectRef obj = (CFObjectRef)system;

    ArtemisEntitySystemSetWorld(system, this);
    ArtemisEntitySystemSetPassive(system, passive);
    CFMapSet(this->systems, NewString((char*)obj->cls->name), system);
    CFBagAdd(this->systemsBag, system);
    return system;
}

/**
 * Removed the specified system from the world.
 * @param system to be deleted from world.
 */
void ArtemisWorldDeleteSystem(
    ArtemisWorldRef this, 
    ArtemisEntitySystemRef system)
{
    CFObjectRef obj = (CFObjectRef)system;
    CFMapSet(this->systems, NewString((char*)obj->cls->name), nullptr);
    CFBagRemove(this->systemsBag, system);
}

void ArtemisWorldNotifySystems(
    ArtemisWorldRef this, 
    ArtemisPerform perform, 
    ArtemisEntityRef e)
{
    for (ulong i=0; i<CFBagSize(this->systemsBag); i++) {
        perform(CFBagGet(this->systemsBag, i), e);
    }
}

void ArtemisWorldNotifyManagers(
    ArtemisWorldRef this, 
    ArtemisPerform perform, 
    ArtemisEntityRef e)
{
    for (ulong i=0; i<CFBagSize(this->managersBag); i++) {
        perform(CFBagGet(this->managersBag, i), e);
    }
}

/**
 * Retrieve a system for specified system type.
 * 
 * @param type type of system.
 * @return instance of the system in this world.
 */
ArtemisEntitySystemRef ArtemisWorldGetSystem(
    ArtemisWorldRef this, 
    CFClassRef cls)
{
    return CFMapGet(this->systems, cls);
}

/**
 * Performs an action on each entity.
 * @param entities
 * @param performer
 */
void ArtemisWorldCheck(
    ArtemisWorldRef this, 
    CFBagRef entities, 
    ArtemisPerform performer)
{
    if (!CFBagIsEmpty(entities)) {
        for (ulong i=0, s=CFBagSize(entities); s>i; i++) {
            ArtemisEntityRef e = CFBagGet(entities, i);
            ArtemisWorldNotifyManagers(this, performer, e);
            ArtemisWorldNotifySystems(this, performer, e);
        }
        CFBagClear(entities);
    }
}

/**
 * Process all non-passive systems.
 */
void ArtemisWorldProcess(
    ArtemisWorldRef this)
{
    (ArtemisWorldRef)this;

    ArtemisWorldCheck(this, this->added, ^(ArtemisManagerRef m, ArtemisEntityRef e) {
        ArtemisManagerAdded(m, e);
    });
    ArtemisWorldCheck(this, this->changed, ^(ArtemisManagerRef m, ArtemisEntityRef e) {
        ArtemisManagerChanged(m, e);
    });
    ArtemisWorldCheck(this, this->disable, ^(ArtemisManagerRef m, ArtemisEntityRef e) {
        ArtemisManagerDisabled(m, e);
    });
    ArtemisWorldCheck(this, this->enable, ^(ArtemisManagerRef m, ArtemisEntityRef e) {
        ArtemisManagerEnabled(m, e);
    });
    ArtemisWorldCheck(this, this->deleted, ^(ArtemisManagerRef m, ArtemisEntityRef e) {
        ArtemisManagerDeleted(m, e);
    });

    ArtemisComponentManagerClean(this->cm);

    for (ulong i=0; i<CFBagSize(this->systemsBag); i++) {
        ArtemisEntitySystemRef system = CFBagGet(this->systemsBag, i);
        if (ArtemisEntitySystemIsPassive(system)) {
            ArtemisEntitySystemProcess(system);
        }
    }

}

/**
 * Retrieves a ComponentMapper instance for fast retrieval of components from entities.
 * 
 * @param type of component to get mapper for.
 * @return mapper for specified component type.
 */
ArtemisComponentMapperRef ArtemisWorldGetMapper(
    ArtemisWorldRef this, 
    CFClassRef cls)
{
    return ArtemisComponentMapperGetFor(cls, this);
}

/**
 * Set an Entity Template
 *
 * @param entityTag
 * @param entityTemplate
 */
void ArtemisWorldSetEntityTemplate(
    ArtemisWorldRef this, 
    CFStringRef name, 
    CFObjectRef cls)
{
    (ArtemisWorldRef)this;
    (CFStringRef)name;
    (CFObjectRef)cls;
}

/**
 * Creates a entity from template.
 *
 * @param name
 * @param args
 * @returns {Entity}
 * EntityTemplate
 */
ArtemisEntityRef ArtemisWorldCreateEntityFromTemplate(
    ArtemisWorldRef this, 
    CFStringRef name, 
    ...)
{
    (ArtemisWorldRef)this;
    (CFStringRef)name;
    return nullptr;
}
