#include "player.hpp"

void Player1::GetPosition(float x, float y)
{
    this->positionX = x + width / 3;
    this->positionY = y - height / 2;
}

void Player1::Draw()
{
    DrawRectangleRounded(Rectangle{positionX, positionY, width, height}, 0.3, 80, WHITE);
}

void Player1::Move()
{
    if (IsKeyDown(KEY_W))
    {
        this->positionY -= speed;
    }
    else if (IsKeyDown(KEY_S))
    {
        this->positionY += speed;
    }
    Limit();
}

void Player1::Limit()
{
    if (positionY <= 0)
    {
        positionY = 0;
    }
    else if (positionY + height >= GetScreenHeight())
    {
        positionY = GetScreenHeight() - height;
    }
}
void Player2::GetPosition(float x, float y)
{
    this->positionX = x - width - width / 3;
    this->positionY = y - height / 2;
}

void Player2::Move()
{
    if (IsKeyDown(KEY_UP))
    {
        this->positionY -= speed;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        this->positionY += speed;
    }
    Limit();
}

void AI::GetBall(Ball *ball)
{
    this->ball = ball;
}

void AI::GetPosition(float x, float y)
{
    this->positionX = x - width - width / 3;
    this->positionY = y - height / 2;
}

void AI::Move()
{
    if (ball->positonY > this->positionY + this->height / 2)
    {
        this->positionY -= speed;
    }
    if (ball->positonY <= this->positionY + this->height / 2)
    {
        this->positionY += speed;
    }
    Limit();
}
