#pragma once
#include "corefw/cfstring.h"
#include "corefw/class.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include <stdint.h>
#include "menu.h"
#include "wasm4.h"

typedef struct __Config* ConfigRef;
extern CFClassRef Config;

typedef struct __Game* GameRef;

struct __Config {
    struct __CFObject obj;

    uint8_t*    data;
    long        x;
    long        y;    
    uint32_t    width;
    uint32_t    height;
    uint32_t    flags;
    int         tick;
};
    
ConfigRef method Ctor(ConfigRef, GameRef);

void method Initialize(ConfigRef);
void method Update(ConfigRef);
void method Draw(ConfigRef);
void method Move(ConfigRef, long, long);
long method GetWidth(ConfigRef);
long method GetHeight(ConfigRef);

static inline ConfigRef NewConfig(GameRef game)
{
    return Ctor((ConfigRef)CFCreate(Config),game);
}