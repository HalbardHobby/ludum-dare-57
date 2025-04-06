#pragma once
#include "raylib.h"

#define TILE_SIZE   4         // Tiles size 8x8 pixels
#define MAP_SIZE_Y  180
#define MAP_SIZE_X  180
#define PLAYER_TILE_VISIBILITY      16
#define PLAYER_PASSIVE_VISIBILITY   5
#define PLAYER_VIEW_ANGLE           60

typedef struct {
    unsigned int tilesX;            // Number of tiles in X axis
    unsigned int tilesY;            // Number of tiles in Y axis
    unsigned char *tileIds;         // Tile ids (tilesX*tilesY), defines type of tile to draw
    unsigned char *tileFog;         // Tile fog state (tilesX*tilesY), defines if a tile has fog or half-fog
}Map;

void InitMap(Map *map);                                     // Inits map variables for fog of war rendering
void RenderMap(Map *map);                                   // Renders map to canvas
//void MarkTilesExplored(Map *map, Vector2 *Tiles);           // Mark tiles as explored
void UpdateFogOfWar(Map *map, RenderTexture2D fogOfWar);    // Updates fow status
void RenderFogOfWar(RenderTexture2D fogOfWar);              // Renders Fog of war texture into canvas
