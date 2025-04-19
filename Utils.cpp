#include "Utils.h" 

Texture2D SECRET_HOME_SCREEN_BACKROUND;
Texture2D HOME_SCREEN_BACKROUND;
Image ICON;

void LoadAssets()
{
    ICON = LoadImage("res/icon.png");
    HOME_SCREEN_BACKROUND = LoadTexture("res/Home_Screen.png");
    SECRET_HOME_SCREEN_BACKROUND = LoadTexture("res/Home_Screen.png");//TODO add this
}

Color GetRandomColor() {
    int nr = GetRandomValue(0, 6);
    switch(nr) 
    {
        case 0:
            return I_COLOR;
        case 1:
            return N_COLOR;
        case 2:
            return P_COLOR;
        case 3:
            return L_COLOR;
        case 4:
            return T_COLOR;
        case 5:
            return O_COLOR;
        case 6:
            return V_COLOR;
    }

    return V_COLOR;
}
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