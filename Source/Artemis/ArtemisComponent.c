/**
 * A tag class. All components in the system must extend this class.
 * 
 * @author Arni Arent
 */
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisComponent);

ArtemisComponentRef method Ctor(ArtemisComponentRef this)
{
    return this;
}
