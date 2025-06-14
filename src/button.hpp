#include <raylib.h>

class Button
{
private:
    Vector2 position; // button position
    Texture texture;  // button texture

public:
    Button(const char *IMGpath, Vector2 IMGposition, float scale); // loading texture
    ~Button();                                                     // unloading texture
    void Draw();                                                   // drawing button
    bool isPressed(bool mouseKeyPressed);                          // checking if button was pressed
};