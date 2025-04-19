#include "Utils.h"
#include "Game.h"

#include "Home_Screen.h"

int const BUTTON_WIDTH = 362;
int const BUTTON_HEIGHT = 115;
int const BUTTON_X = 220;
int const BUTTON_Y = 645;
float scale = 0.5f; 

void InitWindow() 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Atestat");
    SetTargetFPS(200);

    LoadAssets();

    SetWindowIcon((Image)(ICON));
}

bool IsButtonClicked() 
{
    if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return false;

    if(GetMouseX() < BUTTON_X || GetMouseX() > BUTTON_WIDTH + BUTTON_X)
        return false;

    if(GetMouseY() < BUTTON_Y || GetMouseY() > BUTTON_HEIGHT + BUTTON_Y)
        return false;

    return true;
}

void DrawLayout() 
{ 
    ClearBackground(WHITE);

    DrawTextureEx((Texture2D) HOME_SCREEN_BACKROUND, {0,0}, 0.0f, scale, WHITE);
}

void ShowHomeScreen()
{
    InitWindow();

    while(!IsButtonClicked() && !WindowShouldClose())
    {
        BeginDrawing();
        
        DrawLayout();

        EndDrawing();
    }

    UnloadTexture(HOME_SCREEN_BACKROUND);

    if(WindowShouldClose())
        CloseWindow();
    else
        StartGame();
}
