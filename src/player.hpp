#pragma once
#include <raylib.h>

class Player1
{
public:
    const float speed = 10, width = GetScreenWidth() / 28, height = GetScreenHeight() / 5;
    float positionX, positionY;

    void GetPosition(float x, float y);
    void Draw();
    void Move();
    void Limit();
};

class Player2 : public Player1
{
public:
    void GetPosition(float x, float y);
    void Draw();
    void Move();
};