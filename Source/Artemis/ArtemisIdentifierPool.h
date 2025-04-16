#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisIdentifierPool
 */
extern CFClassRef ArtemisIdentifierPool;
typedef struct __ArtemisIdentifierPool* ArtemisIdentifierPoolRef;

typedef struct __ArtemisIdentifierPool {
    __CFObject  obj;
    CFBagRef    ids;
    ulong       nextAvailableId;
} __ArtemisIdentifierPool;

ArtemisIdentifierPoolRef method Ctor(ArtemisIdentifierPoolRef);
ulong ArtemisIdentifierPoolCheckOut(ArtemisIdentifierPoolRef);
void ArtemisIdentifierPoolCheckIn(ArtemisIdentifierPoolRef, ulong);

static inline ArtemisIdentifierPoolRef NewArtemisIdentifierPool()
{
    return Ctor((ArtemisIdentifierPoolRef)CFCreate(ArtemisIdentifierPool));
}
