#include "button.hpp"

Button::Button()
{
}

Button::~Button()
{
    UnloadTexture(texture);
}

Button::Button(const char *IMGpath, float scale)
{
    this->IMGpath = IMGpath;
    image = LoadImage(IMGpath);
    imgWidth = image.width * scale;
    int height = image.height * scale;
    ImageResize(&image, imgWidth, height);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

void Button::DrawIMG_btn(Vector2 IMGposition, float scale)
{
    position = IMGposition;
    position.x -= imgWidth / 2;
    rec = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    DrawTextureV(texture, position, WHITE);
}

void Button::Draw_Text_btn(const char *text, float x, float y, float size, Color color, float width, float height)
{
    rec = {x, y, width, height};
    DrawRectangle(x, y, width, height, Transparent);
    DrawText(text, x, y, size, color);
}

void Button::Draw_Text_Centered_btn(const char *text, float x, float y, float size, Color color, float width, float height)
{
    CustomText cText;
    rec = {x, y, width, height};
    DrawRectangle(x, y, width, height, Transparent);
    cText.DrawCentered_DEFAULT_btn(text, x, y, size, color, width);
}

bool Button::isPressed(bool mouseKeyPressed)
{
    if (CheckCollisionPointRec(GetMousePosition(), rec) && mouseKeyPressed)
    {
        return true;
    }
    return false;
}
