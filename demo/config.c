#include "corefw/cfstring.h"
#include "wasm4.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include "config.h"

static struct __CFClass class = {
	.name = "Config",
	.size = sizeof(struct __Config),
};
CFClassRef Config = &class;

/**
 * Config 
 * 
 * set the properties of a new Config
 *
 * @param name
 */
ConfigRef method Ctor(ConfigRef this, GameRef game)
{
    (ConfigRef)this;
    (GameRef)game;

    this->x = 0;
    this->y = 0;
    this->height = 0;
    this->width = 0;
    this->data = NULL;
    this->flags = 0;
    this->tick = 0;
    
    return this;
}



void method Initialize(ConfigRef this)
{
    (ConfigRef)this;
}

void method Update(ConfigRef this)
{
    (ConfigRef)this;
    this->tick++;
}

void method Draw(ConfigRef this)
{
    (ConfigRef)this;
    // blit(this->data, 0, 0, this->width, this->height, this->flags);
}

void method Move(ConfigRef this, long x, long y)
{
    (ConfigRef)this;
    (long)x;
    (long)y;

    this->x = x;
    this->y = y;
}

long method GetWidth(ConfigRef this)
{
    (ConfigRef)this;
    return (long)this->width;
}
long method GetHeight(ConfigRef this)
{
    (ConfigRef)this;
    return (long)this->height;
}
