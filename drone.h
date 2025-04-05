/*******************************************************************************************
*
*   Describes the drone to be controlled by the player
*
********************************************************************************************/
#include "raylib.h"

typedef struct {
    Vector2 position;
    int size;
    float rotation; // Current drone ration

    float integrity;
    float speed;
    float rotationSpeed;
} Drone;

void Advance(Drone* drone, int direction);
void Rotate(Drone* drone, int direction);
void Render(Drone* drone);
