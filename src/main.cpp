#include "connect.hpp"
//* Game Scenes
typedef enum Scene
{
    MAINMENU = 0,
    LOCAL,
    AI_GAME,
    PASUE,
    SETTINGS
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
    bool local = true;
    //* SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Ping Pong"); // Initializing window

    SetTargetFPS(60);

    Scene current_scene = MAINMENU;

    Ball ball{screenWidth / 2, screenHeight / 2, colors.Yellow};
    Player1 player1;
    Player2 player2;
    AI ai;
    ai.GetBall(&ball);
    Button pause{"../Assets/Pause.png", 1};
    Button ToMainMenu;
    Button resume;
    Rectangle pasuseMenu{screenWidth * 0.3f, screenHeight / 8, screenWidth * 0.4f, screenHeight * 0.75f};
    // main menu
    Button PlayTwoPlayer;
    Button PlayAi;
    Button GameSettings;
    Button Modules{"../Assets/Gear.png", 1};
    CustomText Title;
    CustomText Settings;
    CustomText Accelerate;
    Button accel{"../Assets/Star.png", 0.8f};
    Button GoBack;

    // Setting up starting positions for both players and AI

    //* MAIN GAME LOOP

    while (!WindowShouldClose())
    {
        //* UPDATE
        {
            switch (current_scene)
            {
            case MAINMENU: // MAINMENU scene
            {
                if (PlayTwoPlayer.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                {
                    current_scene = LOCAL;
                    local = true;
                    player1.GetPosition(0, screenHeight / 2);
                    player2.GetPosition(screenWidth, screenHeight / 2);
                    ai.GetPosition(screenWidth, screenHeight / 2);
                }
                if (PlayAi.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                {
                    current_scene = AI_GAME;
                    local = false;
                    player1.GetPosition(0, screenHeight / 2);
                    player2.GetPosition(screenWidth, screenHeight / 2);
                    ai.GetPosition(screenWidth, screenHeight / 2);
                }
                if (Modules.isPressed(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
                {
                    current_scene = SETTINGS;
                }
            }
            break;

            case LOCAL: // GAME scene
            {
                ball.Move();
                player1.Move();
                player2.Move();
                if (ball.lastTouch) // checking for collison with left player (player 1)
                {
                    ball.Check(player1.positionX, player1.positionY, player1.width, player1.height);
                }
                if (!ball.lastTouch) // checking for collsion with right player (player 2)
                {
                    ball.Check(player2.positionX, player2.positionY, player2.width, player2.height);
                }

                if (pause.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE)) // checking if pause button/key is pressed
                {
                    current_scene = PASUE;
                }
            }
            break;

            case AI_GAME:
            {
                ball.Move();
                player1.Move();
                ai.Move();
                if (ball.lastTouch) // checking for collison with left player (player 1)
                {
                    ball.Check(player1.positionX, player1.positionY, player1.width, player1.height);
                }
                if (!ball.lastTouch) // checking for collsion with right player (player 2)
                {
                    ball.Check(ai.positionX, ai.positionY, ai.width, ai.height);
                }

                if (pause.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE)) // checking if pause button/key is pressed
                {
                    current_scene = PASUE;
                }
            }
            break;

            case PASUE: // PASUE active
            {
                if (resume.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_SPACE)) // checking if pause button/key is pressed
                {
                    current_scene = local ? LOCAL : AI_GAME;
                }
                if (ToMainMenu.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) // checking if main menu button is pressed
                {
                    current_scene = MAINMENU;
                    player1.GetPosition(0, screenHeight / 2);
                    player2.GetPosition(screenWidth, screenHeight / 2);
                    ai.GetPosition(screenWidth, screenHeight / 2);
                    ball.player1_score = 0;
                    ball.player2_score = 0;
                    ball.positonX = screenWidth / 2;
                    ball.positonY = screenHeight / 2;
                    ball.lastTouch = true;
                    ball.speed_x = -10;
                    ball.speed_y = 10;
                }
            }
            break;

            case SETTINGS:
            {
                if (accel.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                {
                    ball.accelerate = !ball.accelerate;
                    if (ball.accelerate)
                    {
                        accel.ImgChange("../Assets/BlackStar.png", 0.8f);
                    }
                    else if (!ball.accelerate)
                    {
                        accel.ImgChange("../Assets/Star.png", 0.8f);
                    }
                }
                if (GoBack.isPressed(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                {
                    current_scene = MAINMENU;
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
                ClearBackground(colors.Green);                                                      // background
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);               // left half of the table
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen); // circle in the middle
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);             // net
                // draw Main Menu
                DrawRectangle(0, 0, screenWidth, screenHeight, colors.Transparent);
                Title.DrawCentered_DEFAULT("Ping Pong", screenWidth / 2, 0, 150, WHITE);
                Modules.DrawIMG_btn(Vector2{static_cast<float>(Modules.imgWidth) / 2, screenHeight - Modules.imgHeight});
                PlayTwoPlayer.Draw_Text_Centered_btn("Play local", screenWidth / 2.7f, 230, 100, WHITE, screenWidth / 4, screenHeight / 9);
                PlayAi.Draw_Text_Centered_btn("Play with bot", screenWidth / 2.7f, 360, 100, WHITE, screenWidth / 4, screenHeight / 9);
            }
            break;
            case LOCAL: // GAME scene
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
                pause.DrawIMG_btn(Vector2{screenWidth / 2, 0});                                                        // draw pause button
            }
            break;

            case AI_GAME:
            {
                ClearBackground(colors.Green);                                                                         // background
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);                                  // left half of the table
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen);                    // circle in the middle
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);                                // net
                ball.Draw();                                                                                           // drawing ball
                player1.Draw();                                                                                        // drawing left player
                ai.Draw();                                                                                             // drawing right player
                DrawText(TextFormat("%i", ball.player1_score), screenWidth / 4 - 40, 30, screenHeight / 7, WHITE);     // left player score
                DrawText(TextFormat("%i", ball.player2_score), screenWidth * 0.75f - 40, 30, screenHeight / 7, WHITE); // right player score
                pause.DrawIMG_btn(Vector2{screenWidth / 2, 0});                                                        // draw pause button
            }
            break;

            case PASUE:
            {
                ClearBackground(colors.Green);                                                      // background
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);               // left half of the table
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen); // circle in the middle
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);             // net
                ball.Draw();                                                                        // drawing ball
                player1.Draw();                                                                     // drawing left player
                if (local)
                {
                    player2.Draw(); // drawing right player
                }
                else
                {
                    ai.Draw(); // drawing right player
                }
                DrawText(TextFormat("%i", ball.player1_score), screenWidth / 4 - 40, 30, screenHeight / 7, WHITE);     // left player score
                DrawText(TextFormat("%i", ball.player2_score), screenWidth * 0.75f - 40, 30, screenHeight / 7, WHITE); // right player score
                pause.DrawIMG_btn(Vector2{screenWidth / 2, 0});                                                        // draw pasue button
                // draw pause menu
                DrawRectangle(0, 0, screenWidth, screenHeight, colors.Transparent);
                DrawRectangleRounded(pasuseMenu, 0.2f, 80, colors.Pause);
                DrawText("Pause", screenWidth * 0.3f + (screenWidth * 0.4f) / 5, screenHeight / 8 + (screenHeight * 0.75) / 10, 100, WHITE);
                resume.Draw_Text_Centered_btn("Resume", screenWidth * 0.3f, screenHeight / 2.7f, 80, WHITE, screenWidth * 0.4f, screenHeight / 9);
                ToMainMenu.Draw_Text_Centered_btn("Main Menu", screenWidth * 0.3f, screenHeight / 2, 80, WHITE, screenWidth * 0.4f, screenHeight / 9);
            }
            break;

            case SETTINGS:
            {
                ClearBackground(colors.Green);                                                      // background
                DrawRectangle(0, 0, screenWidth / 2, screenHeight, colors.DarkGreen);               // left half of the table
                DrawCircle(screenWidth / 2, screenHeight / 2, screenHeight / 6, colors.LightGreen); // circle in the middle
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, LIGHTGRAY);             // net
                DrawRectangle(0, 0, screenWidth, screenHeight, colors.Transparent);
                DrawRectangleRounded(pasuseMenu, 0.2f, 80, colors.Pause);
                Settings.DrawCentered_DEFAULT("Settings", screenWidth / 2, screenHeight / 8 + (screenHeight * 0, 75) / 10, 100, WHITE);
                Accelerate.DrawCentered_DEFAULT("Ball accelerates", screenWidth / 2.2f, screenHeight / 8 + screenHeight / 5, 30, WHITE);
                accel.DrawIMG_btn(Vector2{screenWidth / 2.2f + 160, screenHeight / 8 + screenHeight / 5.3f});
                GoBack.Draw_Text_Centered_btn("Go Back", screenWidth/3.35f, screenHeight*7/8 - 80, 80, WHITE, screenWidth * 0.4f, 80);
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
