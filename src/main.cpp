#include <raylib.h>
#include "ball.hpp"
#include "player.hpp"
#include "button.hpp"

typedef enum Scene
{
    MAINMENU = 0,
    GAME,
    PASUE,
} Scene;

struct Colors
{
    Color Green{38, 185, 154, 255};
    Color DarkGreen{20, 160, 133, 255};
    Color LightGreen{129, 204, 184, 255};
    Color Yellow{243, 213, 91, 255};
};
Colors colors;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Ping Pong Game");

    SetTargetFPS(60);

    Scene current_scene = GAME;

    Ball ball{screenWidth / 2, screenHeight / 2, colors.Yellow};
    Player1 player1;
    Player2 player2;
    Button pause{"../Assets/Pause.png", Vector2{screenWidth / 2, 0}, 1};
    player1.GetPosition(0, screenHeight / 2);
    player2.GetPosition(screenWidth, screenHeight / 2);
    //* MAIN GAME LOOP
    while (!WindowShouldClose())
    {
        //* UPDATE
        {
            switch (current_scene)
            {
            case MAINMENU:
            {
            }
            break;

            case GAME:
            {
                ball.Move();
                player1.Move();
                player2.Move();
                if (ball.lastTouch)
                {
                    ball.Chcek(player1.positionX, player1.positionY, player1.width, player1.height);
                }
                if (!ball.lastTouch)
                {
                    ball.Chcek(player2.positionX, player2.positionY, player2.width, player2.height);
                }

                if (pause.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE))
                {
                    current_scene = PASUE;
                }
            }
            break;

            case PASUE:
            {
                if (pause.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE))
                {
                    current_scene = GAME;
                }
            }
            break;

            default:
                break;
            }
        }

        //* DRAW

        BeginDrawing();
        {
            switch (current_scene)
            {
            case MAINMENU:
            {
            }
            break;
            case GAME:
            {
                ClearBackground(colors.Green);
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen);
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);
                ball.Draw();
                player1.Draw();
                player2.Draw();
                DrawText(TextFormat("%i", ball.player1_score), screenWidth / 4 - 40, 30, screenHeight / 7, WHITE);
                DrawText(TextFormat("%i", ball.player2_score), screenWidth * 0.75f - 40, 30, screenHeight / 7, WHITE);
                pause.Draw();
            }
            break;

            case PASUE:
            {
                ClearBackground(colors.Green);
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen);
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);
                ball.Draw();
                player1.Draw();
                player2.Draw();
                DrawText(TextFormat("%i", ball.player1_score), screenWidth / 4 - 40, 30, screenHeight / 7, WHITE);
                DrawText(TextFormat("%i", ball.player2_score), screenWidth * 0.75f - 40, 30, screenHeight / 7, WHITE);
                pause.Draw();
            }
            break;

            default:
                break;
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
