#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h> // Added for sprintf print score and final score

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

int main()
{
}
