#pragma once
#include "../EntityManager.h"
#include "../Game.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"

class ColliderComponent: public Component
{
private:

public:
    std::string colliderTag;
    SDL_Texture* texture;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent* transform;
    bool debugBox;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
    {
        texture = Game::assetManager->GetTexture("collision-image");
        this->colliderTag = colliderTag;
        this->collider = {x, y, width, height};
        this->debugBox = false;
    }
    ~ColliderComponent(){};

    void ToggleDebugMode() override
    {
        debugBox = !debugBox;
    }

    void Initialize() override
    {
        if(owner->HasComponent<TransformComponent>())
        {
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle = {0, 0, transform->width, transform->height};
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltaTime) override 
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;

        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;
    }

    void Render() override
    {
        if(debugBox)
        {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
    }
};


