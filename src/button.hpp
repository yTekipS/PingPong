#include <raylib.h>

class Button
{
public:
    Vector2 position;               // button position
    Texture texture;                // button texture
    Color Transparent{0, 0, 0, 10}; // background for text
    Rectangle rec;

public:
    Button(const char *IMGpath, Vector2 IMGposition, float scale);                             // loading texture
    Button();                                                                                  // empty constructor
    ~Button();                                                                                 // unloading texture
    void Draw();                                                                               // drawing button
    void Draw_Text(const char *text, float x, float y, float size, float width, float height); // draw clickable text
    bool isPressed(bool mouseKeyPressed);                                                      // checking if button was pressed
};