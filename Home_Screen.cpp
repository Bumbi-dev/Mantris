#include "Utils.h"

#include "Home_Screen.h"

int const BUTTON_WIDTH = 362;
int const BUTTON_HEIGHT = 115;
int const BUTTON_X = 220;
int const BUTTON_Y = 645;
float scale = 0.5f; 

Texture2D texture;

void InitWindow() 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Manu Tetris");
    SetTargetFPS(200);
    SetWindowIcon(LoadImage("res/icon.png"));
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


    DrawTextureEx(texture, {0,0}, 0.0f, scale, WHITE);
}

void ShowHomeScreen()
{
    InitWindow();

    texture = LoadTexture("res/Home_Screen.png"); //TODO load this sooner maybe utils method for loading


    while(!IsButtonClicked() && !WindowShouldClose())
    {
        BeginDrawing();
        
        DrawLayout();

        EndDrawing();
    }

    UnloadTexture(texture);

    if(WindowShouldClose())
        CloseWindow();
}
