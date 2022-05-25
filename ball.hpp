#include "raylib.h"

class Ball
{
public:
    float x, y, radius, speedX, speedY;

    Ball(float aX, float aY, float aRadius, float aSpeedX, float aSpeedY)
    {
        x = aX;
        y = aY;
        radius = aRadius;
        speedX = aSpeedX;
        speedY = aSpeedY;
    }

    void draw()
    {
        DrawCircle(x, y, radius, WHITE); // white
    }
};
