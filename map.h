#pragma once

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

// TODO: Init skips every 2 lines, duplicated lines to acomodate.
char *sampleMap =
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............................11............................11............................1"
"1............111111..........11............................11............111111..........1"
"1............111111..........11............................11............111111..........1"
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
"1....1....#####............1.11....1.....................1.11....1....#####............1.1"
"1....1....#####............1.11....1.....................1.11....1....#####............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#............1.11....1....#...#............1.11....1....#...#............1.1"
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#...#....11111111.1.1....1....#...#....11111111.1.1....1....#...#....11111111.1."
"1....1....#####....1.......G1.1....1....#####.....1......G1.1....1....#####....1.......G1."
"1....1....#####....1.......G1.1....1....#####.....1......G1.1....1....#####....1.......G1."
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
"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";;