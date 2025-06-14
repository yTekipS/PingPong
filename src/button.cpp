#include "button.hpp"

Button::Button(const char *IMGpath, Vector2 IMGposition, float scale)
{
    position = IMGposition;
    Image image = LoadImage(IMGpath);
    int width = image.width;
    int height = image.height;
    rec = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    ImageResize(&image, width, height);
    position.x -= width / 2;
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Button::Button()
{
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::Draw()
{
    DrawTextureV(texture, position, WHITE);
}

void Button::Draw_Text(const char *text, float x, float y, float size, float width, float height)
{
    rec = {x, y, width, height};
    DrawRectangle(x, y, width, height, Transparent);
    DrawText(text, x + width / 4.5f, y, size, WHITE);
}

bool Button::isPressed(bool mouseKeyPressed)
{
    if (CheckCollisionPointRec(GetMousePosition(), rec) && mouseKeyPressed)
    {
        return true;
    }
    return false;
}
