/**
 * Config
 *
 * get the pet name
 *
 * @see https://wasm4.org/play/text-input
 */
 #pragma once
#include "corefw/cfstring.h"
#include "corefw/class.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include <stdint.h>
#include "wasm4.h"

extern CFClassRef Config;

typedef struct __Config* ConfigRef;
typedef struct __Game* GameRef;
typedef struct { int x, y; } Keyplace;

typedef enum 
{
    Widget_Delete,
    Widget_Clear,
    Widget_Done,
    Widget_Keyboard,
    Widget_COUNT,   
} Widget;

typedef enum 
{
    Modal_Widgets,
    Modal_KeyboardOpen,
    Modal_TypeSomething,
} Modal;

typedef struct 
{
    Widget      w_select; /* selected widget */
    Modal       modal;
    Keyplace    kb_select;
    char        input[6];
    int         input_len;
    uint8_t     button_cooldown[6];
} State;

/**
 * Config instance variables
 */
typedef struct __Config 
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
    State       state;
} __Config;
    
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

static inline int mod(int x, int n) 
{
    return ((x % n) + n) % n;
}
