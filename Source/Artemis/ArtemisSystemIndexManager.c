/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
#include "artemis.h"    // IWYU pragma: keep

ArtemisSystemIndexManagerClass ArtemisSystemIndexManager = { .index = 0, .indices = nullptr};


ulong ArtemisSystemIndexManagerGetIndexFor(CFClassRef es) 
{
    if (ArtemisSystemIndexManager.indices == nullptr) {
        ArtemisSystemIndexManager.indices = CFCreate(CFMap, nullptr);
    }

    CFIntRef index = CFMapGet(ArtemisSystemIndexManager.indices, es);
    if (index == nullptr) {
        index = CFCreate(CFInt, ArtemisSystemIndexManager.index++);
        CFMapSet(ArtemisSystemIndexManager.indices, es, index);
    }
    return (ulong)CFIntValue(index);
}