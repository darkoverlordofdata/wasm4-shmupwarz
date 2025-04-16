#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep0
/**
 *  @class ArtemisSystemIndexManager
 */

typedef struct ArtemisSystemIndexManagerClass {
    int         index;
    CFMapRef    indices;
} ArtemisSystemIndexManagerClass;


ulong ArtemisSystemIndexManagerGetIndexFor(CFClassRef es);
