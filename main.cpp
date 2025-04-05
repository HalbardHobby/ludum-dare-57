//-------------------------------------------
// Framework includes & definitions
//-------------------------------------------

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

// Misc. dev variables
bool showMessageBox = false;
Drone sampleDrone;

Vector2 previous_position;
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
    sampleDrone = {Vector2{screenWidth/2, screenHeight/2}, 1, 0.f, 100, 60, 60};
    obstacle = {20, 20, 200, 200};
}

void UpdateState(void){
    if (IsKeyDown(KEY_D)) RotateDrone(&sampleDrone, 1); 
    if (IsKeyDown(KEY_A)) RotateDrone(&sampleDrone, -1); 
    if (IsKeyDown(KEY_W)) AdvanceDrone(&sampleDrone, 1); 
    if (IsKeyDown(KEY_S)) AdvanceDrone(&sampleDrone, -1); 
}

void HandleCollisions(void){
    bool collision = CheckCollisionCircleRec(sampleDrone.position, sampleDrone.size*32, obstacle);
    if (!collision) previous_position = sampleDrone.position;
    else {
        Vector2 currentPosition = sampleDrone.position;
        sampleDrone.position.x = previous_position.x;
        collision = CheckCollisionCircleRec(sampleDrone.position, sampleDrone.size*32, obstacle);
        if (!collision) return;

        sampleDrone.position = currentPosition;
        sampleDrone.position.y = previous_position.y;
        collision = CheckCollisionCircleRec(sampleDrone.position, sampleDrone.size*32, obstacle);
        if (!collision) return;

        sampleDrone.position = previous_position;
    }
}

void UpdateGameFrame(void)
{
    ClearBackground(LIGHTGRAY);  // Clear render texture background color
    DrawRectangleRec(obstacle, DARKGRAY);
    RenderDrone(&sampleDrone);

    if (GuiTextBox((Rectangle){ 1, 1, (int)(screenWidth/5), (int)(screenHeight/10) }, "#191#Show Message", 100, false)) showMessageBox = !showMessageBox;
    GuiTextBox((Rectangle){ (int)(screenWidth/4)*3, 1, (int)(screenWidth/4), (int)(screenHeight/3) }, "textBoxMultiText", 1024, false);
}
