#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Raylib Temple.");

    Rectangle player = {400.0f, 285.0f, 50.0f, 50.0f};

    Camera2D camera = {0};
    camera.target = (Vector2){player.x + 20.0f, player.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    //* MAIN GAME LOOP
    while (!WindowShouldClose())
    {
        //* UPDATEa
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if (IsKeyDown(KEY_W))
            player.y -= 2;
        else if (IsKeyDown(KEY_S))
            player.y += 2;
        if (IsKeyDown(KEY_A))
            player.x -= 2;
        else if (IsKeyDown(KEY_D))
            player.x += 2;

        camera.target = (Vector2){player.x + 20.0f, player.y + 20.0f};
        //----------------------------------------------------------------------------------

        //* DRAW
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
            DrawCircle(400.0f, 285.0f, 40.0f, RED);
            DrawRectangleRec(player, BLUE);
        EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}
