#include <SDL2/SDL.h>
#include <stdio.h>

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
int radius = SCREEN_WIDTH / 5; // Radius of circle

// Initialize window & renderer
int initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialize\n");
        return 0;
    }

    window = SDL_CreateWindow(
        "Hello! this is my circle",
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

// Function to draw circle
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

// Draw everything
void draw()
{
    // Background color: Green
    SDL_SetRenderDrawColor(renderer, 0, 103, 71, 255);
    SDL_RenderClear(renderer);

    // Circle color: Red
    SDL_SetRenderDrawColor(renderer, 218, 41, 28, 255);

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
