//-------------------------------------------
// Framework includes & definitions
//-------------------------------------------

#include <vector>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define MIN(a, b) ((a)<(b)? (a) : (b))

#include <math.h>

//-------------------------------------------
// Game Related imports & Definitions
//-------------------------------------------

#include "drone.h"
#include "map.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int windowWidth = 1280;
const int windowHeight = 720;
const int screenWidth = 320;
const int screenHeight = 180;

Map map;                    // Map and Fog of war
RenderTexture2D fogOfWar;
RenderTexture2D target;     // Virtual screen for letterbox scaling
float scale;

Camera2D camera;

// Misc. dev variables
bool showMessageBox = false;
std::vector<Drone> drones = {};
int activeDroneId;
char* updatetext = "Notificacion2\nNotificacion3\nNotificacion4\nNotificacion5\nNotificacion5\n";

std::vector<Vector2> previous_positions = {};
Rectangle obstacle;

//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------
void InitGameState(void);
void UpdateGameFrame(void);     // Update and draw the game frame
void UpdateState(void);

void HandleCollisions(void);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(windowWidth, windowHeight, "base");
    InitAudioDevice();
    InitGameState();

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // Texture scale filter to use
    scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

    // Filter texture initialization for Fog of war
    fogOfWar = LoadRenderTexture(MAP_SIZE_X, MAP_SIZE_Y);
    SetTextureFilter(fogOfWar.texture, TEXTURE_FILTER_POINT);

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateState();
        HandleCollisions();

        BeginTextureMode(target);
        UpdateGameFrame();
        EndTextureMode();

        // Scale Mouse position to work with raygui.
        SetMouseOffset(-(GetScreenWidth() - (screenWidth*scale))*0.5f, -(GetScreenHeight() - (screenHeight*scale))*0.5f);
        SetMouseScale(1/scale, 1/scale);

        BeginDrawing();
        ClearBackground(GRAY);
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                            (Rectangle){ (GetScreenWidth() - ((float)screenWidth*scale))*0.5f, (GetScreenHeight() - ((float)screenHeight*scale))*0.5f,
                            (float)screenWidth*scale, (float)screenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();

    }

    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------

void InitGameState(void){
    // initial postions: (40,3) (50,3)
    drones.push_back({Vector2{80*TILE_SIZE, 6*TILE_SIZE}, 3, 0.f, 100, 60, 60});
    drones.push_back({Vector2{100*TILE_SIZE, 6*TILE_SIZE}, 3, 0.f, 100, 60, 60});
    previous_positions.push_back(Vector2{80*TILE_SIZE, 6*TILE_SIZE});
    previous_positions.push_back(Vector2{100*TILE_SIZE, 6*TILE_SIZE});
    activeDroneId = 0;
    
    InitMap(&map);

    camera = {0};
    camera.target = drones[activeDroneId].position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void UpdateState(void){
    if (IsKeyDown(KEY_D)) RotateDrone(&drones[activeDroneId], 1); 
    if (IsKeyDown(KEY_A)) RotateDrone(&drones[activeDroneId], -1); 
    if (IsKeyDown(KEY_W)) AdvanceDrone(&drones[activeDroneId], 1); 
    if (IsKeyDown(KEY_S)) AdvanceDrone(&drones[activeDroneId], -1);

    if (IsKeyPressed(KEY_TAB)){
        activeDroneId++;
        activeDroneId %= drones.size();
    }

    // Obtener posición en terminos de la cuadricula para cada dron
    Vector2 positions[drones.size()];
    float rotations[drones.size()];
    for(int i=0; i<drones.size(); i++){
        positions[i].x = (int)((drones[i].position.x + TILE_SIZE/2)/TILE_SIZE);
        positions[i].y = (int)((drones[i].position.y + TILE_SIZE/2)/TILE_SIZE);
        rotations[i] = drones[i].rotation;
    }

    // Iterar sobre la grilla y marcar los visitados
    for(int i=0; i<drones.size(); i++){
        Vector2 p = positions[i];
        float r = rotations[i];
        // Create FoV polygon
        Vector2 polygon[5];
        polygon[0] = p;
        float degreeStep = PLAYER_VIEW_ANGLE/4;
        float angle = r+97.5f-PLAYER_VIEW_ANGLE/2;
        for(int i=1; i<5; i++){
            polygon[i] = {p.x + cosf(DEG2RAD*angle)*PLAYER_TILE_VISIBILITY,
                          p.y + sinf(DEG2RAD*angle)*PLAYER_TILE_VISIBILITY};
            angle += degreeStep;
        }

        for (float y = (p.y - PLAYER_TILE_VISIBILITY); y < (p.y + PLAYER_TILE_VISIBILITY); y++)
            for (float x = (p.x - PLAYER_TILE_VISIBILITY); x < (p.x + PLAYER_TILE_VISIBILITY); x++){
                if ((x >= 0) && (x < (int)map.tilesX) && (y >= 0) && (y < (int)map.tilesY)){
                    Vector2 tile_coordinate = {x+0.5f, y+0.5f};
                    if (CheckCollisionPointPoly(tile_coordinate, polygon, 5) || 
                        CheckCollisionPointCircle(tile_coordinate, p, PLAYER_PASSIVE_VISIBILITY))
                            map.tileFog[(int)(y*map.tilesX + x)] = 1;
                }
            }
        }

    UpdateFogOfWar(&map, fogOfWar);
}

void HandleCollisions(void){
    for(int i=0; i<drones.size(); i++) {
        // obtener las celdas alrededor del personaje
        Vector2 p = drones[i].position;
        p.x = (int)((p.x + TILE_SIZE/2)/TILE_SIZE);
        p.y = (int)((p.y + TILE_SIZE/2)/TILE_SIZE);
        int collisionRange = drones[i].size + 2;

        for (int y = (int)(p.y - collisionRange); y < (int)(p.y + collisionRange); y++)
            for (int x = (int)(p.x - collisionRange); x < (int)(p.x + collisionRange); x++)
                if ((x >= 0) && (x < map.tilesX) && (y >= 0) && (y < map.tilesY)){
                    // obtener celdas con las que puede hacer colisión
                    if(map.tileIds[(int)(y*map.tilesX + x)] == TYPE_TILE_WALL) {
                        // iterar cada celda por colisión
                        float xCoord = x*TILE_SIZE;
                        float yCoord = y*TILE_SIZE;
                        Rectangle currentTile = {xCoord, yCoord, TILE_SIZE, TILE_SIZE}; 
                        bool collision = CheckCollisionCircleRec(drones[i].position, drones[i].size*TILE_SIZE, currentTile);
                        // Resolver colisión
                        //if (!collision) previous_positions[i] = drones[i].position;
                        if (collision) {
                            Vector2 currentPosition = drones[i].position;
                            drones[i].position.x = previous_positions[i].x;
                            collision = CheckCollisionCircleRec(drones[i].position, drones[i].size*TILE_SIZE, currentTile);
                            if (!collision) break;

                            drones[i].position = currentPosition;
                            drones[i].position.y = previous_positions[i].y;
                            collision = CheckCollisionCircleRec(drones[i].position, drones[i].size*TILE_SIZE, currentTile);
                            if (!collision) break;

                            drones[i].position = previous_positions[i];
                        }
                    }         
                }
        previous_positions[i] = drones[i].position;
    }
}

void UpdateGameFrame(void)
{
    ClearBackground(BLACK);  // Clear render texture background color

    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.target = drones[activeDroneId].position;

    // Update game world
    BeginMode2D(camera);
        RenderMap(&map);
        RenderFogOfWar(fogOfWar);
        for(Drone i : drones) RenderDrone(&i);

    EndMode2D();

    // update UI
    GuiLoadStyleDefault();
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);   // WARNING: Word-wrap does not work as expected in case of no-top alignment
    GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);
    GuiTextBox((Rectangle){ (int)(screenWidth/3)*2, 1, (int)(screenWidth/3), (int)(screenHeight/2) }, updatetext, 1024, false);

    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_CENTER);
    GuiToggleGroup((Rectangle){ 1, 1, 80, 20 }, "#1#ONE\n#3#TWO", &activeDroneId);
    //GuiDisable();
}
