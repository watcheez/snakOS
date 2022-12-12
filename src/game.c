#include "game.h"
#include "timer.h"
#include "vga.h"
#include "kb.h"

/* 23 x 23 grid */
#define BACKGROUND_COLOR 0b10010010 /*GRAY*/
#define GAME_BACKGROUND_COLOR 0b11011011 /*LIGHT GRAY*/
#define FRAME_COLOR 0b01001001 /*DARK GRAY*/
#define SNAKE_COLOR 0b00011100 /*PURE GREEN*/
#define APPLE_COLOR 0b11100000 /*PURE RED*/

uint8_t screen[529];


void game_update()
{
    uint8_t x;
    uint8_t y;
    uint8_t c;

    c = 0;

    while (1) {
        c ^= 1;
        x = get_random_uint16(22) + 1;
        timer_wait(1);
        y = get_random_uint16(22) + 1;
        if (c) {
            drawTexture8x8(0, x, y, APPLE_COLOR);
        } else {
            drawTexture8x8(0, x, y, SNAKE_COLOR);
        }
    }
}


void init_game()
{
    size_t i;
    size_t j;
    
    setScreenColor(BACKGROUND_COLOR);
    for (i = 1; i < 24; ++i) {
        for (j = 1; j < 24; ++j) {
            drawTexture8x8(0, i, j, GAME_BACKGROUND_COLOR);
        }
    }
    for (i = 0; i <= 24; ++i) {
        drawTexture8x8(0, 0, i, FRAME_COLOR);
        drawTexture8x8(0, 24, i, FRAME_COLOR);
        drawTexture8x8(0, i, 24, FRAME_COLOR);
        drawTexture8x8(0, i, 0, FRAME_COLOR);
    }

    game_update();
}