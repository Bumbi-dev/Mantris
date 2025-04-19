#include "Utils.h"
#include "Game.h"
#include "Canvas.h"

#include "Home_Screen.h"

Rectangle playButton = {220, 645, 362, 115};
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
    BeginDrawing();//TODO add this in the loop after done testing

    DrawRectangleRec(rectangle, {155,55,55,205});

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
        DrawLayout();

        CheckForSecret();

        if(foundSecret)
            std::cout << "sa gasit";

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
