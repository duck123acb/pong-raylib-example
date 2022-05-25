#include <iostream>
#include "raylib.h"
#include "ball.hpp"
#include "paddle.hpp"

using namespace std;

Ball ball(0, 0, 0, 0, 0);
Paddle player1(0, 0, 0, 0, 0, 0);
Paddle player2(0, 0, 0, 0, 0, 0);
const char *winnerText;

void setup()
{
    ball = Ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 5.0, 150, 100);
    player1 = Paddle(50, GetScreenHeight() / 2, 10, 100, 0, 500);
    player2 = Paddle(GetScreenWidth() - 50, GetScreenHeight() / 2, 10, 100, 0, 500);
    winnerText = nullptr;
}

int main()
{
    // starts a raylib window
    InitWindow(800, 600, "Pong");

    // limits FPS to moniters refresh rate.
    SetWindowState(FLAG_VSYNC_HINT);

    // sets up game variables
    setup();

    // game code
    while (!WindowShouldClose())
    {
        // logic
        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        // check if ball is at bottom or top of screen
        if (ball.y >= GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.speedY *= -1;
        }
        else if (ball.y <= 0)
        {
            ball.y = 0;
            ball.speedY *= -1;
        }

        // checks if w or s arrows are pressed, and moves player1
        if (IsKeyDown(KEY_W))
        {
	    if (player1.speedY < player1.topSpeedY) player1.speedY += 25;
            player1.y -= player1.speedY * GetFrameTime();
        }
        else if (IsKeyDown(KEY_S))
        {
	    if (player1.speedY < player1.topSpeedY) player1.speedY += 25;
            player1.y += player1.speedY * GetFrameTime();
        }
	else if (IsKeyUp(KEY_W) || IsKeyUp(KEY_S)) player1.speedY = 0;

        // checks if up or down arrows are pressed, and moves player2
        if (IsKeyDown(KEY_UP))
        {
            if (player2.speedY < player2.topSpeedY) player2.speedY += 25;
	    player2.y -= player2.speedY * GetFrameTime();
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            if (player2.speedY < player2.topSpeedY) player2.speedY += 25;
	    player2.y += player2.speedY * GetFrameTime();
        }
	else if (IsKeyUp(KEY_UP) || IsKeyUp(KEY_DOWN)) player2.speedY = 0;

	if (player1.y - player1.height / 2 < 0)
	{
		player1.y = player1.height / 2;
	}
	else if (player1.y + player1.height / 2 > GetScreenHeight())
	{
		player1.y = GetScreenHeight() - player1.height / 2;
	}

	if (player2.y - player2.height / 2 < 0)
        {
                player2.y = player2.height / 2;
        }
        else if (player2.y + player2.height / 2 > GetScreenHeight())
        {
                player2.y = GetScreenHeight() - player2.height / 2;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, player1.getRect())) // if collides with player1
        {
            if (ball.speedX < 0) // if ball is going right
            {
                ball.speedX *= -1.1;
                ball.speedY = (ball.y - player1.y) / (player1.height / 2) * ball.speedX;
            }
        }
        else if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, player2.getRect())) // if collides with player2
        {
            if (ball.speedX > 0) // if ball is going left
            {
                ball.speedX *= -1.1;
                ball.speedY = (ball.y - player2.y) / (player2.height / 2) * -ball.speedX;
            }
        }

        if (ball.x < 0) // if ball is off the left side of the screen
        {
            winnerText = "Player 2 won!";
        }
        else if (ball.x > GetScreenWidth()) // if ball is off the right side of the screen
        {
            winnerText = "Player 1 won!";
        }

        if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_SPACE))
        {
            setup();
        }

        // drawing
        // starts drawing the scene
        BeginDrawing();

        ClearBackground(BLACK);

        DrawFPS(10, 10);

        if (winnerText)
        {
            int textWidth = MeasureText(winnerText, 60);
            DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
        }
        else
        {
            player1.draw();
            player2.draw();
            ball.draw();
        }

        // end the drawing of the scene
        EndDrawing();
    }

    // stops the raylib window
    CloseWindow();

    return 0;
}
