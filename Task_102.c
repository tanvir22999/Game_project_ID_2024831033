<<<<<<< HEAD
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Defining screen
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Global variables
int gameIsRunning = 0; // To control program
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Circle properties
int centerX;
int centerY;
int initialRadius = 5;
int radius = 5;
int growthSpeed = 2;
Uint32 lastTime = 0;

// Initialize window & renderer
int initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialize\n");
        return 0;
    }

    window = SDL_CreateWindow(
        "Growing Circle Demo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!window)
    {
        printf("Failed to open window\n");
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Failed to create renderer\n");
        return 0;
    }

    centerX = SCREEN_WIDTH / 2;
    centerY = SCREEN_HEIGHT / 2;
    lastTime = SDL_GetTicks();

    return 1;
}

// Handle input
void process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            gameIsRunning = 0;
    }
}

// Draw filled circle
void drawCircle(int cx, int cy, int r)
{
    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            if (i * i + j * j <= r * r)
            {
                SDL_RenderDrawPoint(renderer, cx + i, cy + j);
            }
        }
    }
}

// Update radius over time
void updateRadius()
{
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastTime > 20)
    {
        radius += growthSpeed;
        lastTime = currentTime;
    }

    if (centerX + radius >= SCREEN_WIDTH ||
        centerX - radius <= 0 ||
        centerY + radius >= SCREEN_HEIGHT ||
        centerY - radius <= 0)
    {
        radius = initialRadius;
    }
}

// Draw everything
void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 106, 78, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 244, 42, 65, 255);

    updateRadius();
    drawCircle(centerX, centerY, radius);

    SDL_RenderPresent(renderer);
}

// Cleanup SDL
void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    gameIsRunning = initializeWindow();

    while (gameIsRunning)
    {
        process_input();
        draw();
    }

    destroyWindow();
    return 0;
}
=======
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Defining screen
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Global variables
int gameIsRunning = 0; // To control program
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Circle properties
int centerX;
int centerY;
int initialRadius = 5;
int radius = 5;
int growthSpeed = 2;
Uint32 lastTime = 0;

// Initialize window & renderer
int initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialize\n");
        return 0;
    }

    window = SDL_CreateWindow(
        "Growing Circle Demo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!window)
    {
        printf("Failed to open window\n");
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Failed to create renderer\n");
        return 0;
    }

    centerX = SCREEN_WIDTH / 2;
    centerY = SCREEN_HEIGHT / 2;
    lastTime = SDL_GetTicks();

    return 1;
}

// Handle input
void process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            gameIsRunning = 0;
    }
}

// Draw filled circle
void drawCircle(int cx, int cy, int r)
{
    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            if (i * i + j * j <= r * r)
            {
                SDL_RenderDrawPoint(renderer, cx + i, cy + j);
            }
        }
    }
}

// Update radius over time
void updateRadius()
{
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastTime > 20)
    {
        radius += growthSpeed;
        lastTime = currentTime;
    }

    if (centerX + radius >= SCREEN_WIDTH ||
        centerX - radius <= 0 ||
        centerY + radius >= SCREEN_HEIGHT ||
        centerY - radius <= 0)
    {
        radius = initialRadius;
    }
}

// Draw everything
void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 106, 78, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 244, 42, 65, 255);

    updateRadius();
    drawCircle(centerX, centerY, radius);

    SDL_RenderPresent(renderer);
}

// Cleanup SDL
void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    gameIsRunning = initializeWindow();

    while (gameIsRunning)
    {
        process_input();
        draw();
    }

    destroyWindow();
    return 0;
}

>>>>>>> e3b947cef64846d3e7c3a7559e81a568b8562ead
