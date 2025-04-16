#pragma once
#include "corefw/corefw.h" // IWYU pragma: keep

extern CFClassRef Clock;
typedef struct __Game*      GameRef;
typedef struct __Clock*     ClockRef;
typedef void (^TickHandler)(ClockRef this, GameRef game);

/**
 * Clock instance variables
 */
typedef struct __Clock 
{
    __CFObject  obj;
    GameRef     game;       // the game object
    long        tick;       // raw tick counter
    long        seconds;    // seconds on clock
    long        minutes;    // minutes on clock
    long        hours;      // hours on clock
    long        times;      // time in seconds since start
    TickHandler onTick;     // called once per second to handle clock tick
} __Clock;


ClockRef method Ctor(ClockRef, GameRef);
void method Tick(ClockRef);
void method SetOnTick(ClockRef, TickHandler);

static inline ClockRef NewClock(GameRef game) 
{
    return Ctor((ClockRef)CFCreate(Clock), game);
}