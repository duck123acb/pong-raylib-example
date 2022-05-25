#include "raylib.h"

class Paddle
{
public:
    float x, y, width, height, speedY, topSpeedY;

    Paddle(float aX, float aY, float aWidth, float aHeight, float aSpeed, float aTopSpeedY)
    {
        x = aX;
        y = aY;
        width = aWidth;
        height = aHeight;
        speedY = aSpeed;
	topSpeedY = aTopSpeedY;
    }

    Rectangle getRect()
    {
        // Rectangle me = {x - width / 2, y - height / 2, width, height};
        // return me;
        return Rectangle{x - width / 2, y - height / 2, width, height};
    }

    void draw()
    {
        DrawRectangleRec(getRect(), WHITE);
    }
};
