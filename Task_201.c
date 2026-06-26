#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h> // Added for sprintf print score and final score
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CELL_SIZE 20
#define MAX_SNAKE_LENGTH 100

typedef struct
{
    int x, y;
} Point;

typedef struct
{
    Point body[MAX_SNAKE_LENGTH];
    int length;
    int dx, dy; // direction
} Snake;

typedef struct
{
    Point pos;
} Food;
// built snake body and position of the snake
void initSnake(Snake *snake)
{
    snake->length = 3;
    for (int i = 0; i < 3; i++)
    { // this loop define intialize snake lenght 3
        snake->body[i].y = SCREEN_HEIGHT / 2;
        snake->body[i].x = SCREEN_HEIGHT / 2 - CELL_SIZE * i;
    }
    snake->dx = CELL_SIZE;
    snake->dy = 0;
}
// movement of snake snake block move last to first one by one
void moveSnake(Snake *snake)
{
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1]; // shift body from end of the block
    }
    snake->body[0].x = snake->dx;
    snake->body[0].y = snake->dy; // head shift dx and dy
}

// cheak collision or not
bool cheakCollision(Snake *snake)
{
    // wall condition if -1 value of head cordinate position x or y or cordiante value geater
    //  then screen hight and screen width then collision occurs
    if (snake->body[0].x < 0 || snake->body[0].y < 0 ||
        snake->body[0].x >= SCREEN_WIDTH || snake->body[0].y >= SCREEN_HEIGHT)
    {
        return true;
    }
    // add self collision of the snake
    for (int i = 1; i < snake->length; i++)
    {
        if (snake->body[0].x == snake->body[i].x &&
            snake->body[0].y == snake->body[i].y)
        {
            return true;
        }
    }
    return false;
}
// food generation in random within screen size
void generate int main()
{
}