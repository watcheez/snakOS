#include "game.h"
#include "timer.h"
#include "vga.h"
#include "kb.h"

/* 23 x 23 grid */
#define BACKGROUND_COLOR 0b10010010 /*GRAY*/
#define GAME_BACKGROUND_COLOR 0b11011011 /*LIGHT GRAY*/
#define FRAME_COLOR 0b01001001 /*DARK GRAY*/

uint8_t screen[529];


void game_update()
{

}


void init_game()
{
    size_t i;
    size_t j;

    setScreenColor(BACKGROUND_COLOR);
    for (i = 0; i < 23; ++i) {
        for (j = 0; j < 23; ++j) {
            drawTexture8x8(0, i, j, GAME_BACKGROUND_COLOR);
        }
    }
    for (i = -1; i < 24; ++i) {
        drawTexture8x8(0, -1, i, FRAME_COLOR);
        drawTexture8x8(0, 23, i, FRAME_COLOR);
        drawTexture8x8(0, i, 23, FRAME_COLOR);
        drawTexture8x8(0, i, -1, FRAME_COLOR);
    }

    drawTexture8x8(0, 0, 0, FRAME_COLOR);
}