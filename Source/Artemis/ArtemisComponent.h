#pragma once
#include "../corefw/corefw.h" // IWYU pragma: keep
/**
* @class ArtemisComponent
*/
extern CFClassRef ArtemisComponent;

typedef struct __ArtemisComponent {
    __CFObject obj;
} __ArtemisComponent;

typedef struct __ArtemisComponent* ArtemisComponentRef;

ArtemisComponentRef method Ctor(ArtemisComponentRef);

static inline ArtemisComponentRef NewArtemisComponent()
{
    return Ctor((ArtemisComponentRef)CFCreate(ArtemisComponent));
}