#include <raylib.h>

class CustomText
{
public:
    const char *text;
    float x, y, size;
    Color color;

    void DrawCentered(const char *text, float x, float y, float size, Color color, float w); // draw text center in both axis
};