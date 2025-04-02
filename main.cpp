#include <iostream>
#include <raylib.h>
#include "Game.h" 
#include "Square.h"
#include "Utils.h"

using namespace std;

int const SCREEN_WIDTH = 800;
int const SCREEN_HEIGHT = 1000;

int main () 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manu Tetris");
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("res/icon.png"));

    // InitLayout();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        InitLayout();

        // UpdateGame();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
