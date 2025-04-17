#include <raylib.h>
#include "Utils.h"

#include "Home_Screen.h"

int const BUTTON_WIDTH = 200;
int const BUTTON_HEIGHT = 100;
int const BUTTON_X = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
int const BUTTON_Y = 500;
float scale = 2.0f; 

Texture2D texture;

void InitWindow() 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Manu Tetris");
    SetTargetFPS(60);
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
    Vector2 position = {120, 100};

    DrawTextureEx(texture, position, 0.0f, scale, WHITE);

    int text_width = MeasureText("ATESTAT INFO", 40);
    DrawText("ATESTAT INFO", (WINDOW_WIDTH - text_width) / 2, 30, 40, WHITE);

    DrawRectangle(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, {255, 255, 255, 55});
}

void ShowHomeScreen()
{
    InitWindow();

    texture = LoadTexture("res/image.png");

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
