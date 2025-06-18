#include "customText.hpp"

void CustomText::DrawCentered(const char *text, float x, float y, float size, Color color, float w)
{
    float new_x = (x + w / 2) - (MeasureText(TextFormat(text), size) / 2);
    DrawText(text, new_x, y, size, color);
}
