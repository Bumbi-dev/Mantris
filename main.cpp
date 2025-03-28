#include <iostream>
#include <raylib.h>
#include <GameInterface.h>

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 1000;


int main () 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Atestat");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawLayout();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
