#include "artemis.h"    // IWYU pragma: keep

class(ArtemisManager);

void ArtemisManagerSetWorld(ArtemisManagerRef this, ArtemisWorldRef world)
{
    this->world = world;
}

