/*******************************************************************************************
*
*   Describes the drone to be controlled by the player
*
********************************************************************************************/
#include "drone.h"
#include "raylib.h"
#include "raymath.h"
#include "colors.h"

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
    // TODO: Use Tile size defined in map.h
    DrawPoly(drone->position, 6, drone->size*4, drone->rotation, MEDIUM);
    DrawPolyLines(drone->position, 6, drone->size*4, drone->rotation, HIGHLIGHT);
    Vector2 dir{0, 16};
    dir = Vector2Rotate(dir, drone->rotation*(PI / 180));
    dir = Vector2Add(drone->position, dir);
    DrawLineV(drone->position, dir, HIGHLIGHT);
}