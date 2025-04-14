#pragma once
#include <stdbool.h>
#include "corefw/cfstring.h"
#include "corefw/class.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include "player.h"
#include "splash.h"
#include "config.h"
#include "clock.h"

extern CFClassRef Game;
typedef struct __Game* GameRef;

typedef enum GameState: unsigned int 
{
    GameStateSplashScreen,
    GameStateInputName,
    GameStateRunning,
    GameStateEnd
} GameState;

// max 1024 bytes
typedef struct player_data 
{
    uint32_t    magic;
    char        name[20];
    long        age;     
} player_data;

/**
 * Game instance variables
 */
typedef struct __Game 
{
    __CFObject      obj;
    CFStringRef     title;
    GameState       state;
    SplashRef       splash;
    PlayerRef       player;
    ConfigRef       config;
    CFRandomRef     rnd;
    ClockRef        clock;
    bool            first;
    unsigned long   frameCounter;
    player_data     data;
} __Game;


GameRef method Ctor(GameRef);
void method Start(GameRef);
void method Update(GameRef);
void method Draw(GameRef);
uint8_t method Pressed(GameRef);

static inline GameRef NewGame()
{
    return Ctor((GameRef)CFCreate(Game));
}

static inline uint16_t SetDrawColors(uint16_t c)
{
    uint16_t prior = *DRAW_COLORS;
    *DRAW_COLORS = c;
    return prior;
}

static inline uint16_t GetDrawColors()
{
    return *DRAW_COLORS;
}

/**
 * GamepadPressed
 *
 * @param bool thisFrameOnly
 */
static inline uint8_t GamepadPressed(bool thisFrameOnly)
{
    static uint8_t  previousGamepad = 0;

    uint8_t gamepad = *GAMEPAD1;
    uint8_t pressed = gamepad;
    if (thisFrameOnly) {
        pressed = gamepad & (gamepad ^ previousGamepad);
    }
    previousGamepad = gamepad;
    return pressed;
}

