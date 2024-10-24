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
#define C2I(x, y) (y-1) * 23 + (x-1)
#define I2X(i) ((i) % 23) + 1
#define I2Y(i) ((i) / 23) + 1
#define UP -23
#define DOWN 23
#define LEFT -1
#define RIGHT 1

uint8_t screen[529]; /*0: empty / 1: snake part / 2: apple*/
uint8_t *apple;
uint16_t snake[529];
uint8_t snakeLength;
int direction;
int captured_direction;

uint8_t game_is_over()
{
    int newHeadX, newHeadY;
    newHeadX = I2X(snake[0]) + I2X(direction) - 1;
    newHeadY = I2Y(snake[0]) + I2Y(direction) - 1;
    
    return (newHeadX < 1 || newHeadX > 23 || newHeadY < 1 || newHeadY > 23);
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
    uint8_t color_after_tail;
    uint8_t type_after_tail;

    tail = snake[snakeLength - 1];

    type_after_tail = EMPTY;
    color_after_tail = GAME_BACKGROUND_COLOR;

    if (screen[snake[0] + direction] == APPLE)
    {
        snakeLength++;
        type_after_tail = SNAKE;
        color_after_tail = SNAKE_COLOR;
    }

    for (i = snakeLength - 1; i > 0; --i)
    {
        snake[i] = snake[i - 1];
        screen[snake[i]] = SNAKE;
    }

    snake[0] += direction;
    head = snake[0];
    
    screen[head] = SNAKE;
    drawTexture8x8(0, I2X(head), I2Y(head), SNAKE_COLOR);
    screen[tail] = type_after_tail;
    drawTexture8x8(0, I2X(tail), I2Y(tail), color_after_tail);
}

void capture_direction(char c)
{
    if (c == 'd') captured_direction = RIGHT;
    else if (c == 's') captured_direction = DOWN;
    else if (c == 'a') captured_direction = LEFT;
    else if (c == 'w') captured_direction = UP;
}

void update_direction(int new_direction)
{
    if (new_direction == RIGHT && direction != LEFT) direction = RIGHT;
    if (new_direction == DOWN && direction != UP) direction = DOWN;
    if (new_direction == LEFT && direction != RIGHT) direction = LEFT;
    if (new_direction == UP && direction != DOWN) direction = UP;
}

void game_update()
{
    while (1)
    {
        update_direction(captured_direction);
        map_update();
        timer_wait(50);

        if (game_is_over())
        {
            game_over();
            break;
        }
    }
}

void init_game()
{
    uint16_t x;
    uint16_t y;
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
    }
    x = get_random_uint16(22) + 1;
    timer_wait(1);
    y = get_random_uint16(22) + 1;

    drawTexture8x8(0, x, y, APPLE_COLOR);
    screen[C2I(x, y)] = APPLE;

    direction = RIGHT;

    addKbListener(capture_direction);
    game_update();
}