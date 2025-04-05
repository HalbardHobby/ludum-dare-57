#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MIN(a, b) ((a)<(b)? (a) : (b))

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int windowWidth = 1280;
const int windowHeight = 720;
const int screenWidth = 320;
const int screenHeight = 180;

RenderTexture2D target;     // Virtual screen for letterbox scaling
float scale;

bool showMessageBox = false;


//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------
void UpdateGameFrame(void);     // Update and draw the game frame
void UpdateState(void);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(windowWidth, windowHeight, "base");
    InitAudioDevice();

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // Texture scale filter to use
    scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateState();
        
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

void UpdateState(void)
{
}

void UpdateGameFrame(void)
{
    ClearBackground(GRAY);  // Clear render texture background color

    DrawText("If executed inside a window,\nyou can resize the window,\nand see the screen scaling!", 10, 25, 20, BLACK);

    if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = !showMessageBox;

    GuiTextBox((Rectangle){ 678, 25, 258, 492 }, "textBoxMultiText", 1024, false);
}
