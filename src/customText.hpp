#include <raylib.h>

class CustomText
{
public:
    const char *text;
    float x, y, size;
    Color color;

    void DrawCentered_DEFAULT_btn(const char *text, float x, float y, float size, Color color, float width); // draw text center in x axis
    void DrawCentered_DEFAULT(const char *text, float x, float y, float size, Color color);                  // draw text center in x axis
};