#include "artemis.h"    // IWYU pragma: keep

class(ArtemisComponentMapper);


/**
 * High performance component retrieval from entities. Use this wherever you
 * need to retrieve components from entities often and fast.
 * 
 * @author Arni Arent
 *
 * @param {ArtemisClass} the class type of the component
 * @param {ArtemisWorld} the world instance
 */
ArtemisComponentMapperRef method Ctor(ArtemisComponentMapperRef this, CFClassRef cls, ArtemisWorldRef world)
{
    this->classType = cls;
    this->world = world;
    this->type = nullptr;
    this->components = nullptr;
    return this;
}


/**
 * Fast but unsafe retrieval of a component for this entity.
 * No bounding checks, so this could throw an ArrayIndexOutOfBoundsExeption,
 * however in most scenarios you already know the entity possesses this component.
 * 
 * @param e the entity that should possess the component
 * @return the instance of the component
 */
CFObjectRef ArtemisComponentMapperGet(ArtemisComponentMapperRef this, ArtemisEntityRef e)
{
    return CFBagGet(this->components, ArtemisEntityGetId(e));
}

/**
 * Fast and safe retrieval of a component for this entity.
 * If the entity does not have this component then null is returned.
 * 
 * @param e the entity that should possess the component
 * @return the instance of the component
 */
CFObjectRef ArtemisComponentMapperGetSafe(ArtemisComponentMapperRef this, ArtemisEntityRef e)
{
    return CFBagGet(this->components, ArtemisEntityGetId(e));
}

/**
 * Checks if the entity has this type of component.
 * @param e the entity to check
 * @return true if the entity has this component type, false if it doesn't.
 */
bool ArtemisComponentMapperHas(ArtemisComponentMapperRef this, ArtemisEntityRef e)
{
    return ArtemisComponentMapperGetSafe(this, e) != nullptr;
}

/**
 * Returns a component mapper for this type of components.
 * 
 * @param type the type of components this mapper uses.
 * @param world the world that this component mapper should use.
 * @return a new mapper.
 */
ArtemisComponentMapperRef ArtemisComponentMapperGetFor(CFClassRef cls, ArtemisWorldRef world)
{
    return CFCreate(ArtemisComponentMapper, cls, world);
}

