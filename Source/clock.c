#include "clock.h"

class(Clock);

ClockRef method Ctor(ClockRef this, GameRef game)
{
    this->game = game;
    this->tick = 0;
    this->hours = 0;
    this->minutes = 0;
    this->seconds = 0;
    this->times = 0;
    return this;
}

void method SetOnTick(ClockRef this, TickHandler onTick)
{
    this->onTick = onTick;
}

void method Tick(ClockRef this)
{
    long tick = this->tick++;
    if ((tick % 60) == 0) {
        this->times++;
        this->seconds++;
        if ((this->seconds % 60) == 0) {
            this->seconds = 0;
            if ((this->minutes % 60) == 0) {
                this->minutes = 0;
                this->hours++;
            }
        }
        if (this->onTick != NULL) {
            this->onTick(this, this->game);
        }
    }

}
