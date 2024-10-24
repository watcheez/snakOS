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

uint8_t screen[529]; /*0: empty / 1: snake part / 2: apple */ 
uint16_t snake[529];
uint8_t snakeLength;
int direction;
int captured_direction;
uint8_t have_to_spawn_an_apple;
uint16_t* score;


uint8_t game_is_over()
{
    int newHeadX, newHeadY;
    newHeadX = I2X(snake[0]) + I2X(direction) - 1;
    newHeadY = I2Y(snake[0]) + I2Y(direction) - 1;
    
    return (newHeadX < 1 || newHeadX > 23 || newHeadY < 1 || newHeadY > 23)
        || screen[snake[0] + direction] == SNAKE;
}

void spawn_an_apple()
{
    uint16_t x;
    uint16_t y;

    do {
        x = get_random_uint16(22) + 1;
        timer_wait(1);
        y = get_random_uint16(22) + 1;
    } while (screen[C2I(x, y)] != EMPTY);

    drawTexture8x8(0, x, y, APPLE_COLOR);
    screen[C2I(x, y)] = APPLE;
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
        have_to_spawn_an_apple = 1;
        ++(*score);
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
    if (c == 'd' && direction != LEFT) captured_direction = RIGHT;
    else if (c == 's' && direction != UP) captured_direction = DOWN;
    else if (c == 'a' && direction != RIGHT) captured_direction = LEFT;
    else if (c == 'w' && direction != DOWN) captured_direction = UP;
}

uint8_t game_update()
{
    while (1)
    {
        direction = captured_direction;

        if (game_is_over())
        {
            removeKbListener(capture_direction);
            return 0;
        }
        
        map_update();

        if (have_to_spawn_an_apple) 
        {
            spawn_an_apple();
            have_to_spawn_an_apple = 0;
            writeIntBackground(8, 1, *score, BACKGROUND_COLOR);
        }
        
        timer_wait(20);

    }
}

uint8_t init_game(uint16_t* out_score)
{
    size_t i;
    size_t j;

    score = out_score;

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
    
    spawn_an_apple();

    direction = RIGHT;
    captured_direction = RIGHT;
    addKbListener(capture_direction);
    
    writeStringBackground(1, 1, "Score: 0", BACKGROUND_COLOR);
    return game_update();
}