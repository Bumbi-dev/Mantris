#include <atomic>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "Game_Interface.h"
#include "I_Piece.h"
#include "L_Piece.h"
#include "O_Piece.h"
#include "P_Piece.h"
#include "T_Piece.h"
#include "V_Piece.h"
#include "N_Piece.h"

using namespace std;
using namespace chrono;

bool game_over = false;
int is_key_down = false;

steady_clock::time_point last_move;

thread t;

const int FALL_DELAY = 300;
atomic<float> speed_multiplier(1.0f);
atomic<int> score(0);

Piece* pieces[10] = {new I_Piece(), new O_Piece(), new V_Piece(), new P_Piece(), new T_Piece(), new L_Piece(), new N_Piece()};

void SpawnRandomPiece()
{
    int random_piece = GetRandomValue(0, 6);
    
    bool end_game = SpawnPiece(*pieces[random_piece]);

    if(end_game)
        game_over = true;
}

void UpdateMove()
{
    if(game_over)
        return;

    //SPEED UP FALLING
    if (!is_key_down) {
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            is_key_down = true;
            speed_multiplier = 5.0f;
        }
    } else {
        if (IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S)) {
            is_key_down = false;
            speed_multiplier = 1.0f;
        }
    }

    //ROTATE PIECE
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        RotatePiece();

    //MOVE PIECE
    int time_since_last_move = duration_cast<milliseconds>(steady_clock::now() - last_move).count();

    if(time_since_last_move < 100)
        return;

    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        if(MovePiece(LEFT))
            last_move = steady_clock::now();

    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        if(MovePiece(RIGHT))
            last_move = steady_clock::now();
}

void UpdateFall()
{
    while(!game_over) {
        while(IsKeyDown(KEY_SPACE))//TODO: remove this after finishing
            this_thread::sleep_for(chrono::milliseconds(1));

        this_thread::sleep_for(chrono::milliseconds(static_cast<int>(FALL_DELAY / speed_multiplier)));
        
        if(PieceFalls()) {
            if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
                score += 3;
        } else {
            score += 100 * DeleteCompletedLines();
            SpawnRandomPiece();
        }
    }
}

void InitLayout()
{
    BeginDrawing();

    ClearBackground(BACKGROUND);
    ClearGrid();

    SpawnRandomPiece();
    DrawGrid();

    UpdateScore(0);

    EndDrawing();

    last_move = steady_clock::now();
    game_over = false;

    t = thread(UpdateFall);
}

void UpdateGame()
{
    BeginDrawing();
    ClearBackground(BACKGROUND);

    UpdateMove();
    DrawGrid();

    UpdateScore(score);

    if(game_over) {
        ShowEndGameScreen();

        if(IsKeyPressed(KEY_SPACE)) 
        {
            ClearGrid();
            game_over = false;
            score = 0;
            
            if(t.joinable())
                t.join();

            speed_multiplier = 1;
            is_key_down = false;

            t = thread(UpdateFall);
            DrawGrid();
        }
    }

    EndDrawing();
}

void InitWindow() 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Manu Tetris");
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("res/icon.png"));
}

void StartGame()
{
    InitWindow();

    InitLayout();
    
    while (!WindowShouldClose())
        UpdateGame();

    CloseWindow();
}