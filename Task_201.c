#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h> // Added for sprintf print score and final score
#include <stdbool.h>

#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 680
#define CELL_SIZE 20
#define MAX_SNAKE_LENGTH 100
int speed = 100;

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
    Point body[MAX_SNAKE_LENGTH];
    int length;
    int dx, dy;
} Snake2;

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
void initSnake2(Snake2 *snake)
{
    snake->length = 3;
    for (int i = 0; i < 3; i++)
    { // this loop define intialize snake lenght 3
        snake->body[i].y = SCREEN_HEIGHT / 2 - 5 - CELL_SIZE * i;
        snake->body[i].x = SCREEN_HEIGHT / 2 - 5;
    }
    snake->dx = 0;
    snake->dy = -CELL_SIZE;
}
// movement of snake snake block move last to first one by one
void moveSnake(Snake *snake)
{
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1]; // shift body from end of the block
    }
    snake->body[0].x += snake->dx;
    snake->body[0].y += snake->dy; // head shift dx and dy
}
void moveSnake2(Snake2 *snake2)
{
    for (int i = snake2->length - 1; i > 0; i--)
    {
        snake2->body[i] = snake2->body[i - 1]; // shift body from end of the block
    }
    snake2->body[0].x += snake2->dx;
    snake2->body[0].y += snake2->dy; // head shift dx and dy
}

// cheak collision or not
bool cheakCollision(Snake *snake, Snake2 *snake2)
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
    for (int i = 0; i < snake2->length; i++)
    {
        if (snake->body[0].x == snake2->body[i].x &&
            snake->body[0].y == snake2->body[i].y)
        {
            return true;
        }
    }
    return false;
}
// snake2
void cheakCollision2(Snake2 *snake)
{
    // wall condition if -1 value of head cordinate position x or y or cordiante value geater
    //  then screen hight and screen width then collision occurs
    if (snake->body[0].x < 0 || snake->body[0].y < 0 ||
        snake->body[0].x >= SCREEN_WIDTH || snake->body[0].y >= SCREEN_HEIGHT)
    {
        snake->body[0].x = (rand() % SCREEN_WIDTH / CELL_SIZE) * CELL_SIZE;
        snake->body[0].y = (rand() % SCREEN_WIDTH / CELL_SIZE) * CELL_SIZE;
    }
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
// Dreaw circle block of the snake
void Draw_circle(SDL_Renderer *renderer, int centerx, int centery, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if (dx * dx + dy * dy <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, centerx + dx, centery + dy);
            }
        }
    }
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
    Snake2 snake2;
    generateFood(&food);
    initSnake(&snake);
    initSnake2(&snake2);
    bool isrunning = true;
    int score = 0;
    SDL_Event e;
    char titleBuffer[100];
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
                    if (snake.dx == 0)
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

        moveSnake(&snake); // movement snake
        moveSnake2(&snake2);
        cheakCollision2(&snake2);

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
            score += 15;
            sprintf(titleBuffer, "Game**#**Score: %d ", score);
            SDL_SetWindowTitle(window, titleBuffer);
            generateFood(&food);
        }

        // Game over condition
        if (cheakCollision(&snake, &snake2))
        {
            isrunning = false;
        }

        // 1.Background color draw clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 2.snake2 coloring
        for (int i = 0; i < snake2.length; i++)
        {
            if (i == snake2.length - 1)
            {
                SDL_Rect rect = {snake2.body[i].x, snake2.body[i].y, CELL_SIZE, CELL_SIZE};

                SDL_SetRenderDrawColor(renderer, 100, (score * 2) % 255, (score * 3) % 255, 255);

                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                if (i == 0)
                {
                    SDL_SetRenderDrawColor(renderer, 130, (score * 1) % 255, (score * 2) % 255, 235);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 60, (score * 3) % 255, (score * 2) % 255, 175); // Solid body color
                }
                Draw_circle(renderer, snake2.body[i].x + CELL_SIZE / 2, snake2.body[i].y + CELL_SIZE / 2, CELL_SIZE / 2); // Draw circle snake block
            }
        }
        for (int i = 0; i < snake.length; i++)
        {
            if (i == snake.length - 1)
            {
                SDL_Rect rect = {snake.body[i].x, snake.body[i].y, CELL_SIZE, CELL_SIZE};

                SDL_SetRenderDrawColor(renderer, 100, (score * 2) % 255, (score * 3) % 255, 255);

                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                if (i == 0)
                {
                    SDL_SetRenderDrawColor(renderer, 130, (score * 1) % 255, (score * 2) % 255, 235);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 60, (score * 3) % 255, (score * 2) % 255, 175); // Solid body color
                }
                Draw_circle(renderer, snake.body[i].x + CELL_SIZE / 2, snake.body[i].y + CELL_SIZE / 2, CELL_SIZE / 2); // Draw circle snake block
            }
        }

        // 3.Food coloring using renderer
        SDL_SetRenderDrawColor(renderer, 255, (score * 4) % 255, (score * 5) % 255, 255);
        Draw_circle(renderer, food.pos.x + CELL_SIZE / 2, food.pos.y + CELL_SIZE / 2, CELL_SIZE / 2); // drew cirle food block

        // 4. Frame and wait
        SDL_RenderPresent(renderer);
        if (snake.length > 3 && snake.length % 3 == 0)
        {
            if (speed > 50)
                speed -= 10;
        }
        SDL_Delay(speed);
    }
    // game over score board total score show

    sprintf(titleBuffer, "Game Over ***** Final Score: %d", score);
    SDL_SetWindowTitle(window, titleBuffer);
    printf("Final Score: %d\n", score);
    // flash final window color
    SDL_SetRenderDrawColor(renderer, 0, 180, 180, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    // Destroy renderer and window

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}