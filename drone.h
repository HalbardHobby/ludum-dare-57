/*******************************************************************************************
*
*   Describes the drone to be controlled by the player
*
********************************************************************************************/
#include "raylib.h"
#include "map.h"

extern bool showMessage;
extern int currentMessage;

typedef struct {
    Vector2 position;
    int size;
    float rotation; // Current drone ration

    float integrity;
    float speed;
    float rotationSpeed;
    void (*droneAction)(Vector2 position, float rotation, Map* map);
} Drone;

void AdvanceDrone(Drone* drone, int direction);
void RotateDrone(Drone* drone, int direction);
void RenderDrone(Drone* drone);
void LiftFogOfWar(Drone* drone);

// Drone actions
void DrillTile(Vector2 position, float rotation, Map* map);
void ScanTile(Vector2 position, float rotation, Map* map);
