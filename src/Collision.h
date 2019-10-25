#pragma once
#include <SDL2/SDL.h>
class Collision
{
private:

public:
    Collision();
    ~Collision();

    static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect rectangleB);
};