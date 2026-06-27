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
void generateFood(Food *food)
{
    food->pos.x = (rand() % (SCREEN_WIDTH / CELL_SIZE)) * CELL_SIZE;
    food->pos.y = (rand() % (SCREEN_HEIGHT / CELL_SIZE)) * CELL_SIZE;
}
// cheak food eating snake or not
bool cheakFoodcolision(Snake *snake, Food *food)
{
    if (snake->body[0].x == food->pos.x && snake->body[0].y == food->pos.y)
        return true;
    return false;
}
int main()
{
    // varible all intialize
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Game|Score: 0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    srand(time(NULL));
    Food food;
    Snake snake;
    generateFood(&food);
    initSnake(&snake);
    bool isrunning = true;
    int score = 0;
    SDL_Event e;
    char titleBuffer[50];
    // input and controlling snake
    while (isrunning)
    {
        // input
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isrunning = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (snake.dy == 0)
                    {
                        snake.dx = 0;
                        snake.dy = -CELL_SIZE;
                    }
                    break;
                case SDLK_DOWN:
                    if (snake.dy == 0)
                    {
                        snake.dx = 0;
                        snake.dy = CELL_SIZE;
                    }
                    break;
                case SDLK_LEFT:
                    if (snake.dx == 0)
                    {
                        snake.dy = 0;
                        snake.dx = -CELL_SIZE;
                    }
                    break;
                case SDLK_RIGHT:
                    if (snake.dx = 0)
                    {
                        snake.dy = 0;
                        snake.dx = CELL_SIZE;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    moveSnake(&snake); // movement snake

    // Food colision when snake eating food
    // step1 -> increase length of the snake if snake length not over max length
    // step2 -> increase score
    // step3 -> Update window title buffer and show it
    // step4 -> generate new food

    if (cheakFoodcolision(&snake, &food))
    {
        if (snake.length < MAX_SNAKE_LENGTH)
        {
            snake.length += 1;
        }
        score += 10;
        sprintf(titleBuffer, "Game**#**Score: %d ", score);
        SDL_SetWindowTitle(window, titleBuffer);
        generateFood(&food);
    }
    // Game over condition
    if (cheakCollision(&snake))
    {
        isrunning = false;
    }

    // Background color draw
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}