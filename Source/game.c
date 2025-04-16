#include "game.h"
#include "clock.h"
#include "config.h"
#include "player.h"
#include "palette.h"
#include "splash.h"

class(Game);

extern unsigned long frameCounter;

float clamp(float val, float minVal, float maxVal)
{
    float min = (val > minVal) ? val : minVal;
    return (min < maxVal) ? min : maxVal;
}
// wormy
GameRef method Ctor(GameRef this) 
{
    (GameRef)this;
    this->first = true;
    this->state = GameStateSplashScreen;
    this->frameCounter = 0;
    this->splash = NewSplash(this);
    this->config = NewConfig(this);
    this->clock = NewClock(this);
    this->player = NewPlayer(this);
    this->world = NewArtemisWorld();
    SetOnTick(this->clock,  ^(ClockRef clock, GameRef this) {
        (ClockRef)clock;
        (GameRef)this;
        tracef("tick:: %d", (int)clock->times);

    
    });
    diskr(&this->data, sizeof(this->data));
    return this;
}

void method Start(GameRef this) 
{
    (GameRef)this;
    PaletteRef palette = NewPalette();
    Set(palette, "en4");
}

void method Update(GameRef this) 
{
    (GameRef)this;
    this->frameCounter++;
    Tick(this->clock);
    uint8_t pad;

    switch (this->state) {
    case GameStateSplashScreen:
        Update(this->splash);
        
        if (GamepadPressed(true) & BUTTON_1) {
            this->rnd = NewRandom(frameCounter);
            this->first = false;
            this->state = GameStateInputName;
        }
        break;

    case GameStateInputName:
        Update(this->config);
        break;

    case GameStateRunning:
        pad = GamepadPressed(false);
        if (pad & BUTTON_LEFT) {
            this->player->x -=1;
        }
        else if (pad & BUTTON_RIGHT) {
            this->player->x +=1;
        }
        else if (pad & BUTTON_UP) {
            this->player->y -=1;            
        }
        else if (pad & BUTTON_DOWN) {
            this->player->y +=1;            
        }
        Move(this->player, this->player->x, this->player->y);

    case GameStateEnd:

        break;
    }
}

void method Draw(GameRef this) 
{
    (GameRef)this;
    char buf[80];

    switch (this->state) {
    case GameStateSplashScreen:
        Draw(this->splash);
        text("X - Play", 60, 80);

        break;

    case GameStateInputName:
        break;

    case GameStateRunning:
        Draw(this->player);
        break;

    case GameStateEnd:

        break;
    }
}

