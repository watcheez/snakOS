#include "mainmenu.h"
#include "vga.h"
#include "kb.h"
#include "timer.h"
#include "icons.h"
#include "game.h"

uint8_t sentence_blink = 0;
uint8_t game_launched = 0;

void get_input(char c)
{
    if (c = ' ') {
        game_launched = 1;
    }
}

void remove_kb_listeners()
{
    removeKbListener(get_input);
}

void blink()
{
    if (sentence_blink) {
        writeString(14, 12, "Press SPACE");
    } else {
        writeString(14, 12, "           ");
    }

    sentence_blink = sentence_blink ^ 1;
    timer_wait(50);
    if (!game_launched) {
        blink();
    } else {
        load_game();
    }
}

void load_menu()
{
    /*drawIcon(98, 50, logo);*/
    drawIcon(120, 20, logo);
    addKbListener(get_input);
    blink();
}


void load_game()
{
    remove_kb_listeners();
    clearScreen();
    init_game();
}

