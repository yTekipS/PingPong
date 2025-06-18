#include "connect.hpp"

//* Game Scenes
typedef enum Scene
{
    MAINMENU = 0,
    GAME,
    PASUE,
} Scene;

//* Few colors
struct Colors
{
    Color Green{38, 185, 154, 255};
    Color DarkGreen{20, 160, 133, 255};
    Color LightGreen{129, 204, 184, 255};
    Color Yellow{243, 213, 91, 255};
    Color Pause{255, 255, 255, 150};
    Color Transparent{0, 0, 0, 150};
};
Colors colors;

int main(void)
{
    float screenWidth = 1280;
    float screenHeight = 720;

    //* SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Ping Pong Game"); // Initializing window

    SetTargetFPS(60);

    Scene current_scene = GAME;

    Ball ball{screenWidth / 2, screenHeight / 2, colors.Yellow};
    Player1 player1;
    Player2 player2;
    Button pause;
    Button mainMenu;
    Button resume;
    Rectangle pasuseMenu{screenWidth * 0.3f, screenHeight / 8, screenWidth * 0.4f, screenHeight * 0.75f};

    // Setting up starting positions for both players
    player1.GetPosition(0, screenHeight / 2);
    player2.GetPosition(screenWidth, screenHeight / 2);

    //* MAIN GAME LOOP

    while (!WindowShouldClose())
    {
        //* UPDATE
        {
            //* HANDLING WINDOW RESIZING
            /*if (IsWindowResized())
            {
                screenHeight = GetScreenHeight();
                screenWidth = GetScreenWidth();
                player1.GetPosition(0, screenHeight / 2);
                player1.width = screenWidth / 28;
                player1.height = screenHeight / 5;
                player2.GetPosition(screenWidth, screenHeight / 2);
                player2.width = screenWidth / 28;
                player2.height = screenHeight / 5;
                ball.radius = screenHeight / 24;
                ball.positonX = screenWidth / 2;
                ball.positonY = screenHeight / 2;
                pause.position = Vector2{screenWidth / 2, 0};
                pasuseMenu = {screenWidth * 0.3f, screenHeight / 8, screenWidth * 0.4f, screenHeight * 0.75f};
            }*/
            switch (current_scene)
            {
            case MAINMENU: // MAINMENU scene
            {
            }
            break;

            case GAME: // GAME scene
            {
                ball.Move();
                player1.Move();
                player2.Move();
                if (ball.lastTouch) // checking for collison with left player (player 1)
                {
                    ball.Chcek(player1.positionX, player1.positionY, player1.width, player1.height);
                }
                if (!ball.lastTouch) // checking for collsion with right player (player 2)
                {
                    ball.Chcek(player2.positionX, player2.positionY, player2.width, player2.height);
                }

                if (pause.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE)) // chceking if pause button/key is pressed
                {
                    current_scene = PASUE;
                }
            }
            break;

            case PASUE: // PASUE active
            {
                if (resume.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE)) // chceking if pause button/key is pressed
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
            case MAINMENU: // MAINMENU scene
            {
            }
            break;
            case GAME: // GAME scene
            {
                ClearBackground(colors.Green);                                                                         // background
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);                                  // left half of the table
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen);                    // circle in the middle
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);                                // net
                ball.Draw();                                                                                           // drawing ball
                player1.Draw();                                                                                        // drawing left player
                player2.Draw();                                                                                        // drawing right player
                DrawText(TextFormat("%i", ball.player1_score), screenWidth / 4 - 40, 30, screenHeight / 7, WHITE);     // left player score
                DrawText(TextFormat("%i", ball.player2_score), screenWidth * 0.75f - 40, 30, screenHeight / 7, WHITE); // right player score
                pause.DrawIMG_btn("../Assets/Pause.png", Vector2{screenWidth / 2, 0}, 1);                              // draw pause button
            }
            break;

            case PASUE:
            {
                ClearBackground(colors.Green);                                                                         // background
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);                                  // left half of the table
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen);                    // circle in the middle
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);                                // net
                ball.Draw();                                                                                           // drawing ball
                player1.Draw();                                                                                        // drawing left player
                player2.Draw();                                                                                        // drawing right player
                DrawText(TextFormat("%i", ball.player1_score), screenWidth / 4 - 40, 30, screenHeight / 7, WHITE);     // left player score
                DrawText(TextFormat("%i", ball.player2_score), screenWidth * 0.75f - 40, 30, screenHeight / 7, WHITE); // right player score
                pause.DrawIMG_btn("../Assets/Pause.png", Vector2{screenWidth / 2, 0}, 1);
                // draw pasue button
                DrawRectangle(0, 0, screenWidth, screenHeight, colors.Transparent);
                DrawRectangleRounded(pasuseMenu, 0.2f, 80, colors.Pause);
                DrawText("Pause", screenWidth * 0.3f + (screenWidth * 0.4f) / 5, screenHeight / 8 + (screenHeight * 0.75) / 10, 100, WHITE);
                resume.Draw_Text_Centered_btn("Resume", screenWidth * 0.3f, screenHeight / 2.7f, 80, WHITE, screenWidth * 0.4f, screenHeight / 9);
                mainMenu.Draw_Text_Centered_btn("Main Menu", screenWidth * 0.3f, screenHeight / 2, 80, WHITE, screenWidth * 0.4f, screenHeight / 9);
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
