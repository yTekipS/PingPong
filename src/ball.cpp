#include "ball.hpp"

Ball::Ball(float x, float y, Color c)
{
    this->positonX = x;
    this->positonY = y;
    this->c = c;
}

void Ball::Move()
{
    Bounce();
    positonX += speed_x;
    positonY += speed_y;
}

void Ball::Draw()
{
    DrawCircle(positonX, positonY, radius, c);
}

void Ball::Bounce()
{
    if (positonY - radius <= 0 || positonY + radius >= GetScreenHeight())
    {
        speed_y *= -1;
        if (accelerate == true)
        {
            speed_y = speed_y > 0 ? speed_y + 0.3f : speed_y - 0.3f;
        }
    }
    if (positonX + radius >= GetScreenWidth())
    {
        player1_score++;
        Reset();
    }
    if (positonX - radius <= 0)
    {
        player2_score++;
        Reset();
    }
}

void Ball::Reset()
{
    positonX = GetScreenWidth() / 2;
    positonY = GetScreenHeight() / 2;
}

void Ball::Check(float x, float y, float w, float h)
{
    if (CheckCollisionCircleRec(Vector2{positonX, positonY}, radius, Rectangle{x, y, w, h}))
    {
        speed_x *= -1;
        if (accelerate == true)
        {
            speed_x = speed_x > 0 ? speed_x + 0.3f : speed_x - 0.3f;
        }
        lastTouch = !lastTouch;
    }
}
