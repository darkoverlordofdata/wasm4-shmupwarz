/**
 * Splash Screen
 *
 */
#include "corefw/cfstring.h"
#include "wasm4.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include "splash.h"
#include "background.h"

/**
 * Splash class
 */
static __CFClass class = {
    .name = "Splash",
    .size = sizeof(__Splash),
};
CFClassRef Splash = &class;

/**
 * Splash 
 * 
 * set the properties of a new Splash
 *
 * @param name
 */
SplashRef method Ctor(SplashRef this, GameRef game)
{
    (SplashRef)this;    
    (GameRef)game;
 
    this->game = game;
    this->x = 0;
    this->y = 0;
    this->width = backgroundWidth;
    this->height = backgroundHeight;
    this->flags = BLIT_1BPP;
    this->data = (uint8_t*)&background[0];
    return this;
}
 
 
void method Initialize(SplashRef this)
{
    (SplashRef)this;
}
 
void method Update(SplashRef this)
{
    (SplashRef)this;
}
 
void method Draw(SplashRef this)
{
    (SplashRef)this;
    blit((const uint8_t*)this->data, this->x, this->y, this->width, this->height, this->flags);
}
 
void method Move(SplashRef this, long x, long y)
{
    (SplashRef)this;
    (long)x;
    (long)y;
 
    this->x = (int32_t)x;
    this->y = (int32_t)y;
 }
 
long method GetWidth(SplashRef this)
{
    (SplashRef)this;
    return (long)this->width;
}
long method GetHeight(SplashRef this)
{
    (SplashRef)this;
    return (long)this->height;
}
 

