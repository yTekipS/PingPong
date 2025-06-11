#include "raylib.h"

int player1_score = 0;
int player2_score = 0;
int speed_choise[2] = {-1, 1};
class Ball
{
public:
    float x, y, radius = 20;
    int y_speed = 9, x_speed = 9;
    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Reset()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        x_speed *= speed_choise[GetRandomValue(0, 1)];
        y_speed *= speed_choise[GetRandomValue(0, 1)];
    }

    void Move()
    {
        x += x_speed;
        y += y_speed;

        if (x + radius >= GetScreenWidth())
        {
            player1_score++;
            Reset();
        }
        if (x - radius <= 0)
        {
            player2_score++;
            Reset();
        }
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            y_speed *= -1;
        }
    }
};
Ball ball;
class Player
{
public:
    float x, y;
    const int speed = 9;
    const float width = 30.0f, height = 120.0f;

    void Draw()
    {
        DrawRectangle(x, y, width, height, DARKBLUE);
    }

    void Limit()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

    void Move()
    {
        if (IsKeyDown(KEY_W))
        {
            y -= speed;
        }
        else if (IsKeyDown(KEY_S))
        {
            y += speed;
        }
        Limit();
    }
};

Player player1;

class Player2 : public Player
{
public:
    void Draw()
    {
        DrawRectangle(x, y, width, height, DARKPURPLE);
    }

    void Move()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        Limit();
    }
};

Player2 player2;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Ping Pong Game");

    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.x_speed *= speed_choise[GetRandomValue(0, 1)];
    ball.y_speed *= speed_choise[GetRandomValue(0, 1)];

    player1.x = player1.width / 2;
    player1.y = screenHeight / 2 - player1.height / 2;

    player2.x = screenWidth - (player2.width * 1.5f);
    player2.y = screenHeight / 2 - player2.height / 2;
    SetTargetFPS(60);

    //* MAIN GAME LOOP
    while (!WindowShouldClose())
    {
        //* UPDATE
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        ball.Move();
        player1.Move();
        player2.Move();

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height}))
        {
            ball.x_speed *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height}))
        {
            ball.x_speed *= -1;
        }
        //----------------------------------------------------------------------------------

        //* DRAW
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(BLACK);
            ball.Draw();
            player1.Draw();
            player2.Draw();
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, GRAY);
            DrawText(TextFormat("%i", player1_score), screenWidth / 4 + 20, 20, 100, WHITE);
            DrawText(TextFormat("%i", player2_score), screenWidth / 4 + 20 + screenWidth / 2, 20, 100, WHITE);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}
