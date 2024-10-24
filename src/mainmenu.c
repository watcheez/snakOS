#include "mainmenu.h"
#include "vga.h"
#include "kb.h"
#include "timer.h"
#include "icons.h"
#include "game.h"

uint8_t sentence_blink = 0;
uint8_t validation = 0;
uint8_t choice = 0;

void get_validation(char c)
{
    if (c == ' ') {
        validation = 1;
    }
}

void menu_choice(char c)
{
    if (choice == 1 && c == 's') 
    {
        choice = 2;
        writeString(14, 12, "   ");
        writeString(8, 15, "-> ");
    } 
    else if (choice == 2 && c == 'w') 
    {
        choice = 1;
        writeString(14, 12, "-> ");
        writeString(8, 15, "   ");
    }
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
}

void load_menu()
{
    while (1) {
        drawIcon(98, 50, logo);
        // drawIcon(120, 20, logo);
        addKbListener(get_validation);

        while (!validation) {
            blink();
        }
        removeKbListener(get_validation);
        load_game();
        validation = (choice - 1) ^ 1;
    }
}

void game_over() 
{
    clearScreen();
    choice = 1;
    validation = 0;
    addKbListener(menu_choice);
    addKbListener(get_validation);
    writeString(15, 6, "GAME OVER");
    writeString(14, 12, "-> RETRY");
    writeString(11, 15, "BACK TO MAIN MENU");

    while (!validation) {};
    removeKbListener(menu_choice);
    removeKbListener(get_validation);
    clearScreen();
}

void win()
{

}

void load_game()
{
    clearScreen();
    if (init_game()) {
        win();
    } else {
        game_over();
    }
}

