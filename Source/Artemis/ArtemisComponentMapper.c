#include "../artemis.h"
#include "ArtemisEntity.h"

/**
*   Component Mapper Class
*/
typedef struct __ArtemisComponentMapper {
    __CFObject                  obj;
    ArtemisWorldRef             world;
    ArtemisComponentTypeRef     type;
    CFClassRef                  classType;
    CFBagRef                    components;
} __ArtemisComponentMapper;

static __CFClass class = {
    .name = "ArtemisComponentMapper",
    .size = sizeof(__ArtemisComponentMapper),
    .ctor = ctor,
};
CFClassRef ArtemisComponentMapper = &class;


/**
 * High performance component retrieval from entities. Use this wherever you
 * need to retrieve components from entities often and fast.
 * 
 * @author Arni Arent
 *
 * @param {ArtemisClass} the class type of the component
 * @param {ArtemisWorld} the world instance
 */
static bool ctor(void *ptr, va_list args)
{
    ArtemisComponentMapperRef this = ptr;
    this->classType = va_arg(args, CFClassRef);
    this->world = va_arg(args, ArtemisWorldRef);
    this->type = NULL;
    this->components = NULL;
    return true;
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
    return ArtemisComponentMapperGetSafe(this, e) != NULL;
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

