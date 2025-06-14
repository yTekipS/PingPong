#pragma once
#include <raylib.h>

class Ball
{
public:
    bool lastTouch = false;
    int player1_score = 0;
    int player2_score = 0;

private:
    float speed_x = 10, speed_y = 10, radius = GetScreenHeight() / 24, positonX, positonY;
    Color c;

public:
    Ball(float x, float y, Color c);
    void Move();
    void Draw();
    void Bounce();
    void Reset();
    void Chcek(float x, float y, float w, float h);
};