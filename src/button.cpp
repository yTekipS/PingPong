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

void Button::Draw_Text(const char *text, float x, float y, float size, Color color, float width, float height)
{
    rec = {x, y, width, height};
    DrawRectangle(x, y, width, height, Transparent);
    DrawText(text, x, y, size, WHITE);
}

void Button::Draw_Text_Centered(const char *text, float x, float y, float size, Color color, float width, float height)
{
    CustomText cText;
    rec = {x, y, width, height};
    DrawRectangle(x, y, width, height, Transparent);
    cText.DrawCentered(text, x, y, size, color, width);
}

bool Button::isPressed(bool mouseKeyPressed)
{
    if (CheckCollisionPointRec(GetMousePosition(), rec) && mouseKeyPressed)
    {
        return true;
    }
    return false;
}
