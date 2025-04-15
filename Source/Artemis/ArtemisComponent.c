#include "../artemis.h"
/**
 * A tag class. All components in the system must extend this class.
 * 
 * @author Arni Arent
 */
typedef struct __ArtemisComponent {
    __CFObject obj;
} __ArtemisComponent;

static __CFClass class = {
    .name = "ArtemisComponent",
    .size = sizeof(__ArtemisComponent),
    .ctor = ctor,
};
CFClassRef ArtemisComponent = &class;

static bool ctor(void *ptr, va_list args)
{
    (void*)args;
    ArtemisComponentRef this = ptr;

    return true;
}


