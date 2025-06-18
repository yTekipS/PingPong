#include <raylib.h>
#include "customText.hpp"
class Button
{
public:
    Vector2 position;               // button position
    Texture texture;                // button texture
    Color Transparent{0, 0, 0, 10}; // background for text
    Rectangle rec;

public:
    ~Button();                                                                                                           // unloading texture
    void DrawIMG_btn(const char *IMGpath, Vector2 IMGposition, float scale);                                             // drawing button
    void Draw_Text_btn(const char *text, float x, float y, float size, Color color, float width, float height);          // draw clickable text
    void Draw_Text_Centered_btn(const char *text, float x, float y, float size, Color color, float width, float height); // draw clickable text centered x axis or both axis
    bool isPressed(bool mouseKeyPressed);                                                                                // checking if button was pressed
};