#pragma once
#include "corefw/cfstring.h"
#include "corefw/class.h"
#include "corefw/corefw.h" // IWYU pragma: keep

extern CFClassRef Player;

typedef struct __Player* PlayerRef;
typedef struct __Game* GameRef;

/**
 * Player instance variables
 */
typedef struct __Player 
{
    __CFObject  obj;
    GameRef     game;
    uint8_t*    data;
    int32_t     x;
    int32_t     y;    
    uint32_t    width;
    uint32_t    height;                                                    
    uint32_t    flags;
} __Player;

PlayerRef method Ctor(PlayerRef, GameRef);

void method Initialize(PlayerRef);
void method Update(PlayerRef);
void method Draw(PlayerRef);
void method Move(PlayerRef, long, long);
long method GetWidth(PlayerRef);
long method GetHeight(PlayerRef);

static inline PlayerRef NewPlayer(GameRef game)
{
    return Ctor((PlayerRef)CFCreate(Player), game);
}