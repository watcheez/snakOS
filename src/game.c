#include "game.h"
#include "timer.h"
#include "vga.h"
#include "kb.h"

/* 23 x 23 grid */
#define BACKGROUND_COLOR 0b10010010      /*GRAY*/
#define GAME_BACKGROUND_COLOR 0b11011011 /*LIGHT GRAY*/
#define FRAME_COLOR 0b01001001           /*DARK GRAY*/
#define SNAKE_COLOR 0b00010100           /*MEDIUM DARK GREEN*/
#define APPLE_COLOR 0b11100000           /*PURE RED*/
#define EMPTY 0
#define SNAKE 1
#define APPLE 2
#define C2I(x, y) y * 23 + x
#define I2X(i) (i % 23) + 1
#define I2Y(i) (i / 23) + 1
#define DIR(i) !i ? 1 : (i == 1 ? 23 : (i == 2 ? -1 : -23)) /*0: right / 1: down / 2: left / 3: up*/

uint8_t screen[529]; /*0: empty / 1: snake part / 2: apple*/
uint8_t *apple;
uint8_t snake[529];
uint8_t snakeLength;
uint8_t direction;

uint8_t game_is_over()
{
    int newHeadX, newHeadY;
    newHeadX = I2X(snake[0]) + I2X(direction);
    newHeadY = I2Y(snake[0]) + I2Y(direction);

    return (newHeadX <= 1 || newHeadX >= 24 || newHeadY <= 1 || newHeadY >= 24);
}

void game_over()
{
    clearScreen();
    writeString(15, 8, "GAME OVER");
}

void map_update()
{
    int i;
    int tail;
    int head;

    writeInt(1, 4, snake[0]);

    tail = snake[snakeLength - 1];
    drawTexture8x8(0, I2X(tail), I2Y(tail), GAME_BACKGROUND_COLOR);

    if (screen[snake[0] + direction] == APPLE)
    {
        snakeLength++;
        drawTexture8x8(0, I2X(tail), I2Y(tail), SNAKE_COLOR);
    }

    for (i = snakeLength - 1; i > 0; --i)
    {
        snake[i] = snake[i - 1];
    }
    writeInt(1, 3, direction);

    snake[0] += direction;
    head = snake[0];
    writeInt(1, 5, snake[0]);

    drawTexture8x8(0, I2X(head), I2Y(head), SNAKE_COLOR);
}

void game_update()
{
    // uint8_t x;
    // uint8_t y;

    while (1)
    {
        if (game_is_over())
        {
            game_over();
            break;
        }

        timer_wait(100);
        map_update();

        // x = get_random_uint16(22) + 1;
        // timer_wait(1);
        // y = get_random_uint16(22) + 1;
        // drawTexture8x8(0, x, y, APPLE_COLOR);
    }
}

void init_game()
{
    size_t i;
    size_t j;

    setScreenColor(BACKGROUND_COLOR);
    for (i = 1; i < 24; ++i)
    {
        for (j = 1; j < 24; ++j)
        {
            drawTexture8x8(0, i, j, GAME_BACKGROUND_COLOR);
        }
    }
    for (i = 0; i <= 24; ++i)
    {
        drawTexture8x8(0, 0, i, FRAME_COLOR);
        drawTexture8x8(0, 24, i, FRAME_COLOR);
        drawTexture8x8(0, i, 24, FRAME_COLOR);
        drawTexture8x8(0, i, 0, FRAME_COLOR);
    }

    for (i = 0; i < 529; ++i)
    {
        screen[i] = 0;
        snake[i] = 0;
    }

    snakeLength = 3;
    for (i = 0; i < 3; ++i)
    {
        drawTexture8x8(0, 11 - i, 17, SNAKE_COLOR);
        snake[i] = C2I(11 - i, 17);
        writeInt(1, 10 + i, C2I(11 - i, 17));
    }
    direction = DIR(0);

    writeInt(1, 9, snake[0]);
    writeInt(1, 6, C2I(11, 17));
    writeInt(1, 7, I2X(400));
    writeInt(1, 8, I2Y(400));

    game_update();
}