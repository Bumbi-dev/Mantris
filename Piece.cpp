#include <raylib.h>

class Piece {
public:
    bool active_squares[4][8][8];
    Color color;

    virtual ~Piece() = default;
};