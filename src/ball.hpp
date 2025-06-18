#pragma once
#include <raylib.h>

class Ball
{
public:
    bool lastTouch = false; // which player touch ball last
    int player1_score = 0;  // left player score
    int player2_score = 0;  // right player score

    float speed_x = 10zz, speed_y = 10, radius = GetScreenHeight() / 24, positonX, positonY; // ball's x and y speed, radius, current x and y position
    Color c;                                                                               // ball's color

public:
    Ball(float x, float y, Color c);                // initializnig ball's parameters
    void Move();                                    // moving ball
    void Draw();                                    // drawing ball
    void Bounce();                                  // ball bouncing of window borders and if point was scored
    void Reset();                                   // reseting ball's position back to middle of the window
    void Chcek(float x, float y, float w, float h); // chceking for collision with player
};