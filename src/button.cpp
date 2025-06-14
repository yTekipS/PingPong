#include "button.hpp"

Button::Button(const char *IMGpath, Vector2 IMGposition, float scale)
{
    position = IMGposition;
    Image image = LoadImage(IMGpath);
    int width = image.width;
    int height = image.height;

    ImageResize(&image, width, height);
    position.x -= width / 2;
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::Draw()
{
    DrawTextureV(texture, position, WHITE);
}

bool Button::isPressed(bool mouseKeyPressed)
{
    Rectangle rec = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    if (CheckCollisionPointRec(GetMousePosition(), rec) && mouseKeyPressed)
    {
        return true;
    }
    return false;
}
