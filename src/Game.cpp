#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h";
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "Map.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

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

void Game::Initialize(int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        // Non zero returns are errors.
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    if(TTF_Init() != 0)
    {
        // Non zero returns are errors.
        std::cerr << "Error initializing SDL TTF." << std::endl;
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

    LoadLevel(0);

    isRunning = true;

    return;
}

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber)
{
    // Start including new assets to the assetmanager list
    // TODO: Hard coded for testing.
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    assetManager->AddTexture("collision-image", std::string("./assets/images/collision-texture.png").c_str());
    
    assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);
    
    // Create Map
    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);
    // Start including entities and also components for them
    player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    player.AddComponent<KeyboardControlComponent>("up","right","down","left","space");
    player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

    Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
    tankEntity.AddComponent<TransformComponent>(150, 495, 5, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");
    tankEntity.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

    Entity& heliport(manager.AddEntity("heliport", OBSTACLE_LAYER));
    heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    heliport.AddComponent<SpriteComponent>("heliport-image");
    heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 150, 495, 32, 32);

    Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity& labelLevelName(manager.AddEntity("labelLevelName", UI_LAYER));
    labelLevelName.AddComponent<TextLabelComponent>(10, 10, "First Level", "charriot-font", WHITE_COLOR);
}

void Game::ProcessInput()
{
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
        if(event.key.keysym.sym == SDLK_F1)
        {
            manager.SetAllEntitiesDebugFlag();
        }
        break;
    default:
        break;
    }
}

void Game::Update()
{
    // Wait untill 16ms has ellapsed since the last frame
    // TODO: Find best practice here.
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // Delta time is the difference in ticks from last frame converted to seconds.
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value.
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass.
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    HandleCameraMovement();
    CheckCollisions();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    // Clear the buffer
    SDL_RenderClear(renderer);

    if(manager.HasNoEntities())
    {
        return;
    }

    manager.Render();

    // Swap the buffers
    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement()
{
    TransformComponent *mainPlayerTransform = player.GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);    

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
    CollisionType collisionType = manager.CheckCollisions();
    if(collisionType == PLAYER_ENEMY_COLLISION) 
    {
        ProcessGameOver();
    }
    if(collisionType == PLAYER_LEVEL_COMPLETE_COLLISION)
    {
        ProcessNextLevel(1);
    }
}

void Game::ProcessNextLevel(int levelNumber) 
{
    std::cout << "Next Level" << std::endl;
    isRunning = false;
}
void Game::ProcessGameOver() 
{
    std::cout << "Game Over!" << std::endl;
    isRunning = false;
}

void Game::Destroy() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}