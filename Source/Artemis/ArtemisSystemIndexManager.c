#include "artemis.h"
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
typedef struct ArtemisSystemIndexManagerClass {
    int         index;
    CFMapRef    indices;
} ArtemisSystemIndexManagerClass;

ArtemisSystemIndexManagerClass ArtemisSystemIndexManager = { .index = 0, .indices = NULL};


ulong ArtemisSystemIndexManagerGetIndexFor(CFClassRef es) 
{
    if (ArtemisSystemIndexManager.indices == NULL) {
        ArtemisSystemIndexManager.indices = CFCreate(CFMap, NULL);
    }

    CFIntRef index = CFMapGet(ArtemisSystemIndexManager.indices, es);
    if (index == NULL) {
        index = CFCreate(CFInt, ArtemisSystemIndexManager.index++);
        CFMapSet(ArtemisSystemIndexManager.indices, es, index);
    }
    return (ulong)CFIntValue(index);
}