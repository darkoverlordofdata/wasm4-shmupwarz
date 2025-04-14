#pragma once
#include "corefw/cfstring.h"
#include "corefw/class.h"
#include "corefw/corefw.h" // IWYU pragma: keep

extern CFClassRef Palette;

typedef struct __Palette*     PaletteRef;
typedef struct __Game*      GameRef;


/**
 * Palette instance variables
 */
typedef struct __Palette 
{
    __CFObject  obj;
    CFMapRef    data;
} __Palette;

PaletteRef method Ctor(PaletteRef);
extern method void* Get(PaletteRef, char*);
extern method void Set(PaletteRef, char*);

static inline PaletteRef NewPalette() 
{
    return Ctor((PaletteRef)CFCreate(Palette));
}