#include "../artemis.h"
#include "ArtemisManager.h"
#include <assert.h>

static __CFClass class = {
    .name = "ArtemisManager",
    .size = sizeof(__ArtemisManager),
    .ctor = ctor,
};
CFClassRef ArtemisManager = &class;



/**
 * constructor
 * 
 * @param {int} x
 * @param {int} y
 * @param {int} width
 */
static bool ctor(void *ptr, va_list args)
{
    (void*)ptr;
    (void*)args;
    return true;
}


void ArtemisManagerSetWorld(ArtemisManagerRef this, ArtemisWorldRef world)
{
    this->world = world;
}

