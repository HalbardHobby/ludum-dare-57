//-------------------------------------------
// Framework includes & definitions
//-------------------------------------------

#include <vector>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define MIN(a, b) ((a)<(b)? (a) : (b))

//-------------------------------------------
// Game Related imports & Definitions
//-------------------------------------------

#include "drone.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int windowWidth = 1280;
const int windowHeight = 720;
const int screenWidth = 640;
const int screenHeight = 360;

RenderTexture2D target;     // Virtual screen for letterbox scaling
float scale;

Camera2D camera;

// Misc. dev variables
bool showMessageBox = false;
std::vector<Drone> drones = {};
int activeDroneId;

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
    drones.push_back({Vector2{screenWidth/2, screenHeight/4}, 1, 0.f, 100, 60, 60});
    drones.push_back({Vector2{screenWidth/2, screenHeight/2}, 1, 0.f, 100, 60, 60});
    previous_positions.push_back({screenWidth/2, screenHeight/4});
    previous_positions.push_back({screenWidth/2, screenHeight/2});
    activeDroneId = 0;
    obstacle = {20, 20, 200, 200};

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
}

void HandleCollisions(void){
    for(int i=0; i<drones.size(); i++) {
        bool collision = CheckCollisionCircleRec(drones[i].position, drones[i].size*32, obstacle);
        if (!collision) previous_positions[i] = drones[i].position;
        else {
            Vector2 currentPosition = drones[i].position;
            drones[i].position.x = previous_positions[i].x;
            collision = CheckCollisionCircleRec(drones[i].position, drones[i].size*32, obstacle);
            if (!collision) return;

            drones[i].position = currentPosition;
            drones[i].position.y = previous_positions[i].y;
            collision = CheckCollisionCircleRec(drones[i].position, drones[i].size*32, obstacle);
            if (!collision) return;

            drones[i].position = previous_positions[i];
        }
    }
}

void UpdateGameFrame(void)
{
    ClearBackground(LIGHTGRAY);  // Clear render texture background color

    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.target = drones[activeDroneId].position;

    BeginMode2D(camera);
    DrawRectangleRec(obstacle, DARKGRAY);
    for(Drone i : drones) RenderDrone(&i);
    EndMode2D();

    if (GuiTextBox((Rectangle){ 1, 1, (int)(screenWidth/5), (int)(screenHeight/10) }, "#191#Show Message", 100, false)) showMessageBox = !showMessageBox;
    GuiTextBox((Rectangle){ (int)(screenWidth/4)*3, 1, (int)(screenWidth/4), (int)(screenHeight/3) }, "textBoxMultiText", 1024, false);
}
