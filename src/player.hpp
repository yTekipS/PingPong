#pragma once
#include <raylib.h>

class Player1
{
public:
    const float speed = 10;                                              // player's speed,
    float width = GetScreenWidth() / 28, height = GetScreenHeight() / 5; // player's width, height
    float positionX, positionY;                                          // player's current x and y positions

    void GetPosition(float x, float y); // setting up player's starting position
    void Draw();                        // drawing player
    void Move();                        // moving player
    void Limit();                       // limiting player's movment to top and bottom of the window
};

class Player2 : public Player1
{
public:
    void GetPosition(float x, float y);
    void Draw();
    void Move();
};