#include<vector>
#include<raylib.h>

int const TRIANGLE_SIDE = 35;
int const TRIANGLE_PADDING = 5;
int const BACKGROUND_WIDTH = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * 10 ;
int const BACKGROUND_HEIGHT = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * 20;
Color const TRIANGLE_COLOR = {128, 128, 128, 255};

void DrawLeftTriangle(float x, float y)
{
    Vector2 v1 = {x, y };
    Vector2 v2 = {x, y + TRIANGLE_SIDE};
    Vector2 v3 = {x + TRIANGLE_SIDE, y + TRIANGLE_SIDE};

    DrawTriangle(v1, v2, v3, TRIANGLE_COLOR);
}

void DrawRightTriangle(float x, float y)
{
    Vector2 v1 = {x, y };
    Vector2 v2 = {x + TRIANGLE_SIDE, y + TRIANGLE_SIDE};
    Vector2 v3 = {x + TRIANGLE_SIDE, y};

    DrawTriangle(v1, v2, v3, TRIANGLE_COLOR);
}

void DrawGameArea(int posX, int posY) {
    DrawRectangle(posX,posY, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, {145,145,145,255});

    for(int j = 0; j < 20; j++) {
        for(int i = 0; i < 10; i++) {
            DrawLeftTriangle(posX + TRIANGLE_PADDING +  i * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE), 10 + 2 * TRIANGLE_PADDING + j * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE));    
            DrawRightTriangle(posY + 2 * TRIANGLE_PADDING + i * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE), 10 + TRIANGLE_PADDING +  j * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE));
        }
    }
}

void DrawLayout()
{
    ClearBackground(BLACK);

    DrawGameArea(10,10);
}
