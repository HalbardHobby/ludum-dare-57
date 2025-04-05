/*******************************************************************************************
*
*   Describes the drone to be controlled by the player
*
********************************************************************************************/
#include "drone.h"

void Advance(Drone* drone, int direction){

}

void Rotate(Drone* drone, int direction){

}

void Render(Drone* drone){
    // Execute Render
    DrawPoly(drone->position, 5, drone->size, drone->rotation, RED);
}