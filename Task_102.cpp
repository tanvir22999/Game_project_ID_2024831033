#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

// Defining screen
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Global variables
bool gameIsRunning = false; // To control program
SDL_Window* window = NULL;  // Main window
SDL_Renderer* renderer = NULL; // Drawing tool

// Circle properties
int centerX;             // X coordinate of center
int centerY;             // Y coordinate of center
int initialRadius = 5;  // Start radius
int radius = initialRadius; // Current radius
int growthSpeed = 2;     // How fast radius increases
Uint32 lastTime = 0;     // Timer for smooth growth

// Initialize window & renderer
bool initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL failed to initialize\n";
        return false;
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
        cout << "Failed to open window\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cout << "Failed to create renderer\n";
        return false;
    }

    centerX = SCREEN_WIDTH / 2;
    centerY = SCREEN_HEIGHT / 2;
    lastTime = SDL_GetTicks();

    return true;
}

// Handle input
void process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            gameIsRunning = false;
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

    // Update every 20ms for smooth growth
    if (currentTime - lastTime > 20)
    {
        radius += growthSpeed;
        lastTime = currentTime;
    }

    // Reset if collides with window edges
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
    // Background color: green 
    SDL_SetRenderDrawColor(renderer, 0, 106, 78, 255);
    SDL_RenderClear(renderer);

    // Circle color: red
    SDL_SetRenderDrawColor(renderer, 244, 42, 65, 255);

    // Update radius before drawing
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

int main(int argc, char* argv[])
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