#pragma once
#include <SDL2/SDL.h>

// TODO: Prefix engine variables
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

enum CollisionType {
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_OBSTACLE_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

enum LayerType {
    TILEMAP_LAYER = 0,
    OBSTACLE_LAYER = 1,
    ENEMY_LAYER = 2,
    PLAYER_LAYER = 3,
    PROJECTILE_LAYER = 4,
    UI_LAYER = 5
};

const SDL_Color WHITE_COLOR = {255,255,255,255};
const SDL_Color GREEN_COLOR = {0,255,0,255};

const unsigned int NUM_LAYERS = 6;