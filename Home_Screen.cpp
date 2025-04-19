#include "Utils.h"
#include "Game.h"
#include "Canvas.h"

#include "Home_Screen.h"

int const BUTTON_WIDTH = 362;
int const BUTTON_HEIGHT = 115;
int const BUTTON_X = 220;
int const BUTTON_Y = 645;
Rectangle playButton = {BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
float scale = 0.5f; 
bool foundSecret = false;

void InitWindow() 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Atestat");
    SetTargetFPS(200);

    LoadAssets();

    SetWindowIcon(ICON);
}

bool IsRectangleClicked(Rectangle rectangle)
{
    if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return false;

    if(GetMouseX() < rectangle.x || GetMouseX() > rectangle.x + rectangle.width)
        return false;

    if(GetMouseY() < rectangle.y || GetMouseY() > rectangle.y + rectangle.height)
        return false;

    return true;
}

void DrawLayout() 
{ 
    ClearBackground(WHITE);

    if(foundSecret)
        DrawTextureEx(SECRET_HOME_SCREEN_BACKROUND, {0,0}, 0.0f, scale, WHITE);
    else
        DrawTextureEx(HOME_SCREEN_BACKROUND, {0,0}, 0.0f, scale, WHITE);

}

void CheckForSecret()
{
    //TODO add better conditions
    if(IsRectangleClicked((Rectangle) {0,0, 50 ,50}))
        foundSecret = true;
}

void OpenHomeScreen()
{
    InitWindow();

    while(!IsRectangleClicked(playButton) && !WindowShouldClose())
    {
        BeginDrawing();
        
        DrawLayout();

        CheckForSecret();

        EndDrawing();
    }

    UnloadTexture(HOME_SCREEN_BACKROUND);

    if(WindowShouldClose()) {
        CloseWindow();
        return;
    }

    if(foundSecret)
        StartCanvas();
    else
        StartGame();
}
