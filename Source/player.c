#include "player.h"
#include "corefw/cfstring.h"
#include "wasm4.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include <string.h>
#include "spaceship.h"
#include "game.h"

/**
 * Player instance variables
 */
 static __CFClass class = {
	.name = "Player",
	.size = sizeof(__Player),
};
CFClassRef Player = &class;

/**
 * Player 
 * 
 * set the properties of a new player
 *
 * @param name
 */
PlayerRef method Ctor(PlayerRef this, GameRef game)
{
    (PlayerRef)this;
    (GameRef)game;

    this->game = game;
    this->x = 0;
    this->y = 0;
    this->width = spaceshipWidth;
    this->height = spaceshipHeight;
    this->flags = spaceshipFlags;
    this->data = (uint8_t*)&spaceship[0];
    this->mask = 0x0420; // he he 
    return this;
}


void method Initialize(PlayerRef this)
{
    (PlayerRef)this;
}

void method Update(PlayerRef this)
{
    (PlayerRef)this;
}

void method Draw(PlayerRef this)
{
    (PlayerRef)this;
    uint16_t saved = SetDrawColors(this->mask);
    blit(this->data, this->x, this->y, this->width, this->height, this->flags);
    SetDrawColors(saved);
}

void method Move(PlayerRef this, long x, long y)
{
    (PlayerRef)this;
    (long)x;
    (long)y;

    this->x = (int32_t)x;
    this->y = (int32_t)y;
}

long method GetWidth(PlayerRef this)
{
    (PlayerRef)this;
    return (long)this->width;
}
long method GetHeight(PlayerRef this)
{
    (PlayerRef)this;
    return (long)this->height;
}
