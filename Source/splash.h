#pragma once
#include "corefw/corefw.h" // IWYU pragma: keep

extern CFClassRef Splash;

typedef struct __Splash* SplashRef;
typedef struct __Game* GameRef;

/**
 * Splash instance variables
 */
typedef struct __Splash 
{
    __CFObject  obj;
    GameRef     game;
    uint8_t*    data;
    int32_t     x;
    int32_t     y;    
    uint32_t    width;
    uint32_t    height;                                                    
    uint32_t    flags;
    int         tick;
} __Splash;

SplashRef method Ctor(SplashRef, GameRef);

void method Initialize(SplashRef);
void method Update(SplashRef);
void method Draw(SplashRef);
void method Move(SplashRef, long, long);
long method GetWidth(SplashRef);
long method GetHeight(SplashRef);

static inline SplashRef NewSplash(GameRef game)
{
    return Ctor((SplashRef)CFCreate(Splash), game);
}