/*******************************************************************************************
*
*   Describes the drone to be controlled by the player
*
********************************************************************************************/
#include "drone.h"
#include "raylib.h"
#include "raymath.h"
#include "colors.h"
#include "map.h"

bool showMessage = false;
int currentMessage = 0;

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

void DrillTile(Vector2 position, float rotation, Map* map){

    // Obtener posición en terminos de la cuadricula para cada dron
    Vector2 p;
    float r=rotation;
    p.x = (int)((position.x + TILE_SIZE/2)/TILE_SIZE);
    p.y = (int)((position.y + TILE_SIZE/2)/TILE_SIZE);

    // Create FoV polygon
    Vector2 polygon[5];
    polygon[0] = p;
    float degreeStep = PLAYER_VIEW_ANGLE/4;
    float angle = r+97.5f-PLAYER_VIEW_ANGLE/2;
    for(int i=1; i<5; i++){
        polygon[i] = {p.x + cosf(DEG2RAD*angle)*PLAYER_PASSIVE_VISIBILITY,
                      p.y + sinf(DEG2RAD*angle)*PLAYER_PASSIVE_VISIBILITY};
        angle += degreeStep;
    }

    for (float y = (p.y - PLAYER_PASSIVE_VISIBILITY); y < (p.y + PLAYER_PASSIVE_VISIBILITY); y++)
        for (float x = (p.x - PLAYER_PASSIVE_VISIBILITY); x < (p.x + PLAYER_PASSIVE_VISIBILITY); x++){
            if ((x >= 0) && (x < (int)map->tilesX) && (y >= 0) && (y < (int)map->tilesY)){
                Vector2 tile_coordinate = {x+0.5f, y+0.5f};
                if (CheckCollisionPointPoly(tile_coordinate, polygon, 5) && map->tileIds[(int)(y*map->tilesX + x)] == TYPE_TILE_BREAKABLE)
                        map->tileIds[(int)(y*map->tilesX + x)] = TYPE_TILE_EMPTY;
            }
        }
}


void ScanTile(Vector2 position, float rotation, Map* map){
    if(showMessage){
        currentMessage ++;
        showMessage=false;
        return;
    }

    Vector2 p;
    float r=rotation;
    p.x = (int)((position.x + TILE_SIZE/2)/TILE_SIZE);
    p.y = (int)((position.y + TILE_SIZE/2)/TILE_SIZE);

    // Create FoV polygon
    Vector2 polygon[5];
    polygon[0] = p;
    float degreeStep = PLAYER_VIEW_ANGLE/4;
    float angle = r+97.5f-PLAYER_VIEW_ANGLE/2;
    for(int i=1; i<5; i++){
        polygon[i] = {p.x + cosf(DEG2RAD*angle)*PLAYER_PASSIVE_VISIBILITY,
                      p.y + sinf(DEG2RAD*angle)*PLAYER_PASSIVE_VISIBILITY};
        angle += degreeStep;
    }

    bool found = false;
    for (float y = (p.y - PLAYER_PASSIVE_VISIBILITY); y < (p.y + PLAYER_PASSIVE_VISIBILITY); y++)
        for (float x = (p.x - PLAYER_PASSIVE_VISIBILITY); x < (p.x + PLAYER_PASSIVE_VISIBILITY); x++){
            if ((x >= 0) && (x < (int)map->tilesX) && (y >= 0) && (y < (int)map->tilesY)){
                Vector2 tile_coordinate = {x+0.5f, y+0.5f};
                if (CheckCollisionPointPoly(tile_coordinate, polygon, 5) && map->tileIds[(int)(y*map->tilesX + x)] == TYPE_TILE_OBJECTIVE){
                    map->tileIds[(int)(y*map->tilesX + x)] = TYPE_TILE_EMPTY;
                    found = true;
                }
            }
        }
    
    if (found){
        showMessage = true;
    }
}
