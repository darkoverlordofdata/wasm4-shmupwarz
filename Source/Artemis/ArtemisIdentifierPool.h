#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
 *  @class ArtemisIdentifierPool
 */
extern CFClassRef ArtemisIdentifierPool;

typedef struct __ArtemisIdentifierPool* ArtemisIdentifierPoolRef;

ulong ArtemisIdentifierPoolCheckOut(ArtemisIdentifierPoolRef);
void ArtemisIdentifierPoolCheckIn(ArtemisIdentifierPoolRef, ulong);