#include "Utils.h"

Color GetDarkerColor(Color c)
{
    return {
        (unsigned char)(c.r * 0.9),
        (unsigned char)(c.g * 0.9 * 0.95f),
        (unsigned char)(c.b * 0.9 * 1.05f),
        c.a
    };
}
bool AreColorsEqual(Color color1, Color color2) {
    if(color1.r != color2.r)
        return false;
    if(color1.g != color2.g)
        return false;
    if(color1.b != color2.b)
        return false;
    if(color1.a != color2.a)
        return false;

    return true;
}