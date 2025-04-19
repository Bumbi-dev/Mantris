#include "Utils.h"
#include "Game.h"
#include "Canvas.h"

#include "Home_Screen.h"

Rectangle secretButton = {52, 184, 35, 35};
Rectangle playButton = {220, 645, 362, 115};

float scale = 0.5f; 

int timesClicked = 0;
bool foundSecret = false;

//CLICK THE HOLE IN THE "A" TO FIND SECRET
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

    DrawTextureEx(HOME_SCREEN_BACKROUND, {0,0}, 0.0f, scale, WHITE);

    if(foundSecret)
        DrawTextureEx(SECRET_HOME_SCREEN, {221, 645}, 0.0f, 0.4f, WHITE);
}

void CheckForSecret()
{
    if(IsRectangleClicked(secretButton))
        timesClicked++;

    if(timesClicked >= 5)
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
