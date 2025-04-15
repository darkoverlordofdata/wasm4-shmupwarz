#include "artemis.h"

static struct __CFClass class = {
    .name = "ArtemisEntityManager",
    .size = sizeof(struct __ArtemisEntityManager),
    .ctor = ctor,
};
CFClassRef ArtemisEntityManager = &class;

/**
 *
 */
static bool ctor(void *ptr, va_list args)
{
    (void*)args;
    ArtemisEntityManagerRef this = ptr;

    this->entities = CFCreate(CFArray, NULL);
    this->disabled = CFCreate(CFBitVector);
    this->identifierPool = CFCreate(ArtemisIdentifierPool);
    this->active = 0;
    this->added = 0;
    this->created = 0;
    this->deleted = 0;

    static struct ArtemisManagerVtbl const vtbl = { &ArtemisEntityManagerAdded, 
                                                    &ArtemisEntityManagerChanged,
                                                    &ArtemisEntityManagerDeleted,
                                                    &ArtemisEntityManagerDisabled,
                                                    &ArtemisEntityManagerEnabled };
    this->base.vptr = &vtbl;               

    return true;
}

void ArtemisEntityManageSetWorld(ArtemisEntityManagerRef this, ArtemisWorldRef world)
{
    this->base.world = world;
}

ArtemisEntityRef ArtemisEntityManagerCreateEntityInstance(ArtemisEntityManagerRef this, CFStringRef name)
{
    ArtemisEntityRef e = CFCreate(ArtemisEntity, ArtemisIdentifierPoolCheckOut(this->identifierPool), name);
    this->created++;
    return e;
}


/**
 * Check if this entity is active.
 * Active means the entity is being actively processed.
 * 
 * @param entityId
 * @return true if active, false if not.
 */
bool ArtemisEntityManagerIsActive(ArtemisEntityManagerRef this, ulong id)
{ 
    return (CFBagGet(this->entities, id) != NULL);
}

/**
 * Check if the specified entityId is enabled.
 * 
 * @param entityId
 * @return true if the entity is enabled, false if it is disabled.
 */
bool ArtemisEntityManagerIsEnabled(ArtemisEntityManagerRef this, ulong entityId)
{ 
    return Get(this->disabled, (int)entityId);
}

/**
 * Get a entity with this id.
 * 
 * @param entityId
 * @return the entity
 */
ArtemisEntityRef ArtemisEntityManageGetEntity(ArtemisEntityManagerRef this, ulong entityId)
{
    return CFBagGet(this->entities, entityId);
}

/**
 * Get how many entities are active in this world.
 * @return how many entities are currently active.
 */
ulong ArtemisEntityManageGetActiveEntityCount(ArtemisEntityManagerRef this)
{ 
    return this->active;
}

/**
 * Get how many entities have been created in the world since start.
 * Note: A created entity may not have been added to the world, thus
 * created count is always equal or larger than added count.
 * @return how many entities have been created since start.
 */
ulong ArtemisEntityManageGetTotalCreated(ArtemisEntityManagerRef this)
{
    return this->created; 
}

/**
 * Get how many entities have been added to the world since start.
 * @return how many entities have been added.
 */
ulong ArtemisEntityManageGetTotalAdded(ArtemisEntityManagerRef this)
{
    return this->added;
}

/**
 * Get how many entities have been deleted from the world since start.
 * @return how many entities have been deleted since start.
 */
ulong ArtemisEntityManageGetTotalDeleted(ArtemisEntityManagerRef this)
{ 
    return this->deleted;
}


