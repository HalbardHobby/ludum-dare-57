/*******************************************************************************************
*
*   Describes the drone to be controlled by the player
*
********************************************************************************************/
#include "drone.h"
#include "raylib.h"
#include "raymath.h"

void AdvanceDrone(Drone* drone, int direction){
    // Find velocity vector
    Vector2 velocity = {0.f, drone->speed*GetFrameTime()*(float)direction};
    velocity = Vector2Rotate(velocity, drone->rotation*(PI / 180));
    // Add vectors
    drone->position = Vector2Add(drone->position, velocity);
}

void RotateDrone(Drone* drone, int direction){
    drone->rotation += drone->rotationSpeed*GetFrameTime()*(float)direction;
}

void RenderDrone(Drone* drone){
    // Execute Render
    DrawPoly(drone->position, 6, drone->size*32, drone->rotation, RED);
    Vector2 dir{0, 32};
    dir = Vector2Rotate(dir, drone->rotation*(PI / 180));
    dir = Vector2Add(drone->position, dir);
    DrawLineV(drone->position, dir, GREEN);
}