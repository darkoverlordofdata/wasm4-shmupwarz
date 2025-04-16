/**
 * The most raw entity system. It should not typically be used, but you can create your own
 * entity system handling by extending this. It is recommended that you use the other provided
 * entity system implementations.
 * 
 * @author Arni Arent
 *
 */
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisIdentifierPool);

ArtemisIdentifierPoolRef method Ctor(ArtemisIdentifierPoolRef this)
{
    this->ids = CFCreate(CFBag,64);
    return this;
}

ulong ArtemisIdentifierPoolCheckOut(ArtemisIdentifierPoolRef this)
{
    if (CFBagSize(this->ids) > 0) {
        return (ulong)CFIntValue(CFBagRemoveLast(this->ids));
    }
    return this->nextAvailableId;
}

void ArtemisIdentifierPoolCheckIn(ArtemisIdentifierPoolRef this, ulong index)
{
    CFBagAdd(this->ids, NewInt((int64_t)index));
}
