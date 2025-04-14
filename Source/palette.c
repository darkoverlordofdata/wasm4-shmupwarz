#include "palette.h"
#include "wasm4.h"

/**
 * Palette class
 */
static struct __CFClass class = {
    .name = "Palette",
    .size = sizeof(struct __Palette),
};
CFClassRef Palette = &class;

static uint32_t ice_cream_gb[] = { 0xfff6d3, 0xf9a875, 0xeb6b6f, 0x7c3f58 }; 
static uint32_t en4[]          = { 0x20283d, 0x426e5d, 0xe5b083, 0xfbf7f3 }; 

// https://lospec.com/palette-list/en4
// https://lospec.com/palette-list/ice-cream-gb

PaletteRef method Ctor(PaletteRef this)
{
    this->data = CFCreate(CFMap,
		NewString("ice-cream-gb"),  ice_cream_gb,
		NewString("en4"), 		    en4, 
		NULL);
    return this;
}


method void Set(PaletteRef this, char* key) 
{
    uint32_t* p = Get(this, key);
    PALETTE[0] = p[0];
    PALETTE[1] = p[1];
    PALETTE[2] = p[2];
    PALETTE[3] = p[3];
}

method void* Get(PaletteRef this, char* key)
{
    return CFMapGetC(this->data, key);
}
