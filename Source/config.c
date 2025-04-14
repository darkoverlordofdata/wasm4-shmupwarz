/**
 * Config
 *
 * get the pet name
 *
 * @see https://wasm4.org/play/text-input
 */
 #include "corefw/cfstring.h"
#include "player.h"
#include "wasm4.h"
#include "corefw/corefw.h" // IWYU pragma: keep
#include "config.h"
#include "game.h"
#include <stdbool.h>

/**
 * Config class
 */
static __CFClass class = {
	.name = "Config",
	.size = sizeof(__Config),
};
CFClassRef Config = &class;

static Keyplace keyplace_normalize(Keyplace kp);
typedef struct { int x, y; } iVec2;
typedef struct { char *str; int strlen; int offset_px; } Keyboard_Row;

static Keyboard_Row keyboard[] = {
    {"qwertyuiop", 11,    5},
    { "asdfghjkl", 10,    8},
    {   "zxcvbnm",  8,   14}
};

static uint32_t darkoverlordofdata = 0xd16a; // big if true!
static long     default_age = 70;
static float    default_hunger = 50;
static float    default_happiness = 100;
static float    default_money = 500;
static float    default_poop = 0;
static bool     default_sick = false;


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

    this->game = game;
    this->x = 0;
    this->y = 0;
    this->height = 0;
    this->width = 0;
    this->data = NULL;
    this->flags = 0;
    this->tick = 0;

    // reset the state:
    this->state.w_select = Widget_Keyboard;
    this->state.modal = 0;
    this->state.kb_select.x = 0;
    this->state.kb_select.y = 0;
    // this->state.kb_select = keyplace_normalize(this->state.kb_select);
    
    for (int i=0; i<6; i++)
        this->state.input[i] = 0;
    this->state.input_len = 0;
    for (int i=0; i<6; i++)
        this->state.button_cooldown[i] = 0;
    return this;
}


static Keyplace keyplace_normalize(Keyplace kp) 
{
    int old_y = kp.y;
    kp.y = mod(kp.y, 3);

    Keyboard_Row *row = keyboard + kp.y;
    kp.x = mod(kp.x, row->strlen-1);

    return kp;
}

static iVec2 keyplace_to_px(Keyplace kp) 
{
    Keyboard_Row *row = keyboard + kp.y;
    return (iVec2) { 16*kp.x + row->offset_px, 100 + 14*kp.y };
}

static char keyplace_char(Keyplace kp) 
{
    return keyboard[kp.y].str[kp.x];
}

static uint8_t keyplace_eq(Keyplace a, Keyplace b) 
{
    return a.x == b.x && a.y == b.y;
}

static uint8_t button_tap(ConfigRef this, uint8_t button) 
{
    uint8_t gamepad = *GAMEPAD1;
    uint8_t *cooldown = 0;

    if (button == BUTTON_1    ) cooldown = this->state.button_cooldown + 0;
    if (button == BUTTON_2    ) cooldown = this->state.button_cooldown + 1;
    if (button == BUTTON_LEFT ) cooldown = this->state.button_cooldown + 2;
    if (button == BUTTON_RIGHT) cooldown = this->state.button_cooldown + 3;
    if (button == BUTTON_UP   ) cooldown = this->state.button_cooldown + 4;
    if (button == BUTTON_DOWN ) cooldown = this->state.button_cooldown + 5;

    if (*cooldown > 0) *cooldown = *cooldown - 1;

    if ((gamepad & button) && (*cooldown == 0)) {
        *cooldown = 16;
        return 1;
    }
    if (!(gamepad & button)) *cooldown = 0;

    return 0;
}

void method Initialize(ConfigRef this)
{
    (ConfigRef)this;
}

void method Update(ConfigRef this)
{
    (ConfigRef)this;
    this->tick++;

    if (this->game->data.magic == darkoverlordofdata) {
        this->game->player = NewPlayer(this->game);
        this->game->state = GameStateRunning;
        return;
    }

    text("enter name", 35, 10);
    text(this->game->data.name, 40, 20);
    if (this->state.modal == Modal_TypeSomething) {
        text(
            "   Please type at   \n"
            "least one character.\n" 
            "                    \n"
            "                    \n"
            "     \x80=continue  \n",
            0, 60
        );
        if (*GAMEPAD1 > 0 && this->tick > 20) this->state.modal = Modal_Widgets;
        return;
    }
    
    uint16_t select_color = ((this->tick/10)%3 == 0) ? 4 : 3;
    
    {
        uint32_t len = sizeof(this->state.input)-2;
        int x = SCREEN_SIZE/2 - len*8/2;
    
        *DRAW_COLORS = 0x20;
        rect(x-2, 40-3, len*12+4, 8+5);
    
        *DRAW_COLORS = select_color;
        this->state.input[this->state.input_len] = (select_color == 4) ? '|' : '\0';
        this->state.input[5] = '\0';
        text(this->state.input, x, 40);
    }
    
    *DRAW_COLORS = 4;
    for (int y = 0; y < 3; y++) {
        int x = 0;
        char *str = keyboard[y].str;
        while (*str) {
            char tmp[2] = { *str };
            Keyplace kp = { x, y };
            iVec2 px_pos = keyplace_to_px(kp);
        
            if (this->state.modal != Modal_KeyboardOpen)
                *DRAW_COLORS = 3;
            else if (keyplace_eq(kp, this->state.kb_select))
                *DRAW_COLORS = select_color;
            else
                *DRAW_COLORS = 2;
            text(tmp, px_pos.x, px_pos.y);
        
            str++, x++;
        }
    }
    
    char *help = 0;
    
    if (this->state.modal == Modal_KeyboardOpen) {
        *DRAW_COLORS = 0x30;
        help = "\x80=stop    \x81=type";
    } else if (this->state.w_select == Widget_Keyboard) {
        *DRAW_COLORS = (uint16_t) (select_color << 4);
        help = "\x80=start typing";
    } else
        *DRAW_COLORS = 0x20;
    rect(2, 96, 156, 44);
    
    *DRAW_COLORS = 2;
    if (this->state.w_select == Widget_Delete) {
        *DRAW_COLORS = select_color;
        help = "\x80=delete";
    }
    text("delete", 5, 80);
    
    *DRAW_COLORS = 2;
    if (this->state.w_select == Widget_Clear) {
        *DRAW_COLORS = select_color;
        help = "\x80=clear";
    }
    text("clear", 67, 80);
    
    *DRAW_COLORS = 2;
    if (this->state.w_select == Widget_Done) {
        *DRAW_COLORS = select_color;
        help = "\x80=finish";
    }
    text("done", 120, 80);
    
    *DRAW_COLORS = 4;
    text(help, 4, 147);
    
    
    
    if (this->state.modal == Modal_KeyboardOpen) {
    
        if (button_tap(this, BUTTON_RIGHT )) this->state.kb_select.x++;
        if (button_tap(this, BUTTON_LEFT  )) this->state.kb_select.x--;
        if (button_tap(this, BUTTON_UP    )) this->state.kb_select.y--;
        if (button_tap(this, BUTTON_DOWN  )) this->state.kb_select.y++;
    
        if (button_tap(this, BUTTON_1     )) this->state.modal = Modal_Widgets;
        if (button_tap(this, BUTTON_2     ) && this->state.input_len < (int)sizeof(this->state.input))
            this->state.input[this->state.input_len++] = keyplace_char(this->state.kb_select);
        this->state.kb_select = keyplace_normalize(this->state.kb_select);

    } else {
        if (button_tap(this, BUTTON_UP    )) this->state.w_select--;
        if (button_tap(this, BUTTON_DOWN  )) this->state.w_select++;
        if (button_tap(this, BUTTON_1     )) {
            if (this->state.w_select == Widget_Clear)    this->state.input_len = 0;
            if (this->state.w_select == Widget_Delete) this->state.input_len--;
            if (this->state.w_select == Widget_Keyboard)
                this->state.modal = Modal_KeyboardOpen;
            if (this->state.w_select == Widget_Done) {
                trace("Done?");
                if (this->state.input_len == 0) {
                    this->tick = 0, this->state.modal = Modal_TypeSomething;
                }
                else {
                    trace("Done!");
                    for (int i=0; i<5; i++) {
                        this->game->data.name[i] = this->state.input[i];
                    }
                    this->game->data.name[5] = 0;
                    trace(this->game->data.name);
                    this->game->data.magic = darkoverlordofdata;
                    this->game->data.age = default_age;
                    diskw(&this->game->data, sizeof(this->game->data));
                }
            }
        }
        this->state.w_select = (Widget)mod((int)this->state.w_select, Widget_COUNT);
    }
    

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

    this->x = (int32_t)x;
    this->y = (int32_t)y;
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
