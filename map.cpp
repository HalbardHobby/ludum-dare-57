/*******************************************************************************************
*
*   Describes the world map
*
********************************************************************************************/
#include "map.h"
#include "raylib.h"
#include "colors.h"
#include <stdlib.h>

// TODO: Init skips every 2 lines, duplicated lines to acomodate.
char *sampleMap =
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"1............................11............................11............................1"
"1............................11.........................G..11............................1"
"1............................11.........................G..11............................1"
"1............................11............................11............................1"
"1............111111..........11............................11............######..........1"
"1............111111..........11............................11............######..........1"
"1............1....1..........11............................11............1....1..........1"
"1............1....1..........11............................11............1....1..........1"
"1............1....1..........11............................11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1....111111111....11111111...11####111111111....111######..11....111111111....11111111...1"
"1....111111111....11111111...11####111111111....111######..11....111111111....11111111...1"
"1....1......................1.1....1......................1.1....1......................1."
"1....1......................1.1....1......................1.1....1......................1."
"1....1....#####............1.11....1...............G.....1.11....1....#####............1.1"
"1....1....#####............1.11....1...............G.....1.11....1....#####............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#.G.#............1.1"
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#.G.#....11111111.1."
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#####....1........1.1....1....#####.....1.......1.1....1....#####....1........1."
"1....1....#####....1........1.1....1....#####.....1.......1.1....1....#####....1........1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....11111111111111111111111111....11111111111111111111111111....1111111######111111111111"
"1....11111111111111111111111111....11111111111111111111111111....1111111######111111111111"
"1............................11............................##............................1"
"1............................11............................##............................1"
"1............................##............................##............................1"
"1....G.......................##............................##............................1"
"1....G.......................##............................##............................1"
"1............................##............................##............................1"
"1............................##............................##............................1"
"1............................11............................##............................1"
"11111111111###########11111111111111111111111111111111111111111111111111111111111111111111"
"11111111111###########11111111111111111111111111111111111111111111111111111111111111111111"
"11111111111###########11111111111111111111111111111111111111111111111111111111111111111111"
"11111111111###########11111111111111111111111111111111111111111111111111111111111111111111"
"1............................11............................11............................1"
"1............................11............................11...............G............1"
"1............................11............................11...............G............1"
"1............................11............................11............................1"
"1............................11............111111..........11............111111..........1"
"1....G.......................11............111111..........11............111111..........1"
"1....G.......1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11......G.....1....1..........11............1....1..........1"
"1............1....1..........11......G.....1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1....111111111....11111111...11....111111111....11111111...11....111111111....11111111...1"
"1....111111111....11111111...11....111111111....11111111...11....111111111....11111111...1"
"1....1......................1.1....1......................1.1....1......................1."
"1....1......................1.1....1......................1.1....1......................1."
"1....1....#####............1.11....1....#####............1.11....1....#####............1.1"
"1....1....#####............1.11....1....#####............1.11....1....#####............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#####....1.......G1.1....1....#####....1........1.1....1....#####....1........1."
"1....1....#####....1.......G1.1....1....#####....1........1.1....1....#####....1........1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#...G..1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#...G..1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1.......................11....1.......................11....1.......................1"
"1....1.......................11....1.......................11....1.......................1"
"1....11111111#######11111111111....11111111111111111111111111....1111111111111111111111111"
"1....11111111#######11111111111....11111111111111111111111111....1111111111111111111111111"
"1............................11............................11............................1"
"1............................##............................11............................1"
"1............................##.................G..........11............................1"
"1............................##.................G..........11............................1"
"1............................##............................11............................1"
"1............................11............................11............................1"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............111111..........11............111111..........11............111111..........1"
"1............111111..........11............111111..........11............111111..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1............1....1..........11............1....1..........11............1....1..........1"
"1....111111111....11111111...11....111111111....11111111...11....111111111....11111111...1"
"1....111111111....11111111...11....111111111....11111111...11....111111111....11111111...1"
"1....1......................1.1....1......................1.1....1......................1."
"1....1......................1.1....1......................1.1....1......................1."
"1....1....#####............1.11....1....#####............1.11....1....#####............1.1"
"1....1....#####............1.11....1....#####............1.11....1....#####............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#####....1.......G1.1....1....#####....1.......G1.1....1....#####....1.......G1."
"1....1....#####....1.......G1.1....1....#####....1.......G1.1....1....#####....1.......G1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..1.......1...1.......1.1....1..1.......1...1.......1.1....1..1.......1...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..111111111...1.......1.1....1..111111111...1.......1.1....1..111111111...1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..............1.......1.1....1..............1.......1.1....1..............1.......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..#....#..#....#......1.1....1..#....#..#....#......1.1....1..#....#..#....#......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1..######..######......1.1....1..######..######......1.1....1..######..######......1."
"1....1.......................11....1.......................11....1.......................1"
"1....1.......................11....1.......................11....1.......................1"
"1....11111111111111111111111111....11111111111111111111111111....1111111111111111111111111"
"1....11111111111111111111111111....11111111111111111111111111....1111111111111111111111111"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";

void InitMap(Map* map){
    // Init map
    *map = {0};
    map->tilesX = MAP_SIZE_X;
    map->tilesY = MAP_SIZE_Y;
    map->tileIds = (unsigned char *)calloc(map->tilesX*map->tilesY, sizeof(unsigned char));
    map->tileFog = (unsigned char *)calloc(map->tilesX*map->tilesY, sizeof(unsigned char));
    
    for (unsigned int y = 0; y < map->tilesY; y++){
        for (unsigned int x = 0; x < map->tilesX; x++){
            // TODO: init skips every 2 lines
            int tile_x = x/2;
            int tile_y = y/2;
            switch (sampleMap[tile_y*map->tilesX + tile_x])
            {
            case '1':
                map->tileIds[y*map->tilesX + x] = TYPE_TILE_WALL;
            break;
            case '#':
                map->tileIds[y*map->tilesX + x] = TYPE_TILE_BREAKABLE;
            break;
            case 'G':
                map->tileIds[y*map->tilesX + x] = TYPE_TILE_OBJECTIVE;
            break;
            default:
                map->tileIds[y*map->tilesX + x] = TYPE_TILE_EMPTY;
                break;
            }
        }
    }
}

void RenderMap(Map *map){
    for (unsigned int y = 0; y < map->tilesY; y++)
        for (unsigned int x = 0; x < map->tilesX; x++){
            Color c;
            switch (map->tileIds[y*map->tilesX + x])
            {
            case TYPE_TILE_WALL:
                c = DARK;
                break;
            case TYPE_TILE_BREAKABLE:
                c = MEDIUM;
                break;
            case TYPE_TILE_OBJECTIVE:
                c = HIGHLIGHT;
                break;
            default:
                c = LIGHT;
                break;
            }
            DrawRectangle(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE, c);
        }
}

void UpdateFogOfWar(Map *map, RenderTexture2D fogOfWar){
    BeginTextureMode(fogOfWar);
        ClearBackground(BLANK);
        for (unsigned int y = 0; y < map->tilesY; y++)
            for (unsigned int x = 0; x < map->tilesX; x++)
                if (map->tileFog[y*map->tilesX + x] == 0) DrawRectangle(x, y, 1, 1, DARK);
    EndTextureMode();

    //Update Fog of war
    for (int i = 0; i < map->tilesX*map->tilesY; i++) 
    if (map->tileFog[i] == 1) 
        map->tileFog[i] = 2;
}

void RenderFogOfWar(RenderTexture2D fogOfWar){
    // Draw fog of war (scaled to full map, bilinear filtering)
    DrawTexturePro(fogOfWar.texture, (Rectangle){ 0, 0, (float)fogOfWar.texture.width, (float)-fogOfWar.texture.height },
                    (Rectangle){ 0, 0, (float)TILE_SIZE*MAP_SIZE_X, (float)TILE_SIZE*MAP_SIZE_Y },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);
}