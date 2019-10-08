#include <iostream>
#include "./Constants.h"
#include "./Game.h"

Game::Game()
{
    this->isRunning = false;
}

Game::~Game()
{

}

bool Game::IsRunning() const 
{
    return this->isRunning;
}

// TODO: Test code. Remove
float projectilePoxX = 0.0f;
float projectilePoxY = 0.0f;
float projectileVelX = 0.1f;
float projectileVelY = 0.1f;

void Game::Initialize(int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        // Non zero returns are errors.
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,                   // Title
        SDL_WINDOWPOS_CENTERED, // X positon of window
        SDL_WINDOWPOS_CENTERED, // Y positon of window
        width,                  // Window width
        height,                 // Winodw height
        SDL_WINDOW_BORDERLESS  // Flags
    );
    // Window fails to create
    if(!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(
        window, // Window to render to
        -1,     // Index of driver: -1 is default driver
        0       // Flags
    );
    // Renderer fails to create
    if(!renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    isRunning = true;

    return;
}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {   
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN: 
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
            isRunning = false;
        }
        break;
    default:
        break;
    }
}

void Game::Update()
{
    projectilePoxX += projectileVelX;
    projectilePoxY += projectileVelY;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    // Clear the buffer
    SDL_RenderClear(renderer);

    SDL_Rect projectile {
        (int)projectilePoxX,
        (int)projectilePoxY,
        10,
        10,
    };
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer, &projectile);

    // Swap the buffers
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}