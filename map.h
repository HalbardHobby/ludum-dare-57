#define TILE_SIZE   8         // Tiles size 8x8 pixels

#define MAP_SIZE_Y  90
#define MAP_SIZE_X  90

typedef struct {
    unsigned int tilesX;            // Number of tiles in X axis
    unsigned int tilesY;            // Number of tiles in Y axis
    short int *tileIds;         // Tile ids (tilesX*tilesY), defines type of tile to draw
    short int *tileFog;         // Tile fog state (tilesX*tilesY), defines if a tile has fog or half-fog
}Map;
