#include <raylib.h>

class Button
{
private:
    Vector2 position;
    Texture texture;

public:
    Button(const char* IMGpath, Vector2 IMGposition, float scale);
    ~Button();
    void Draw();
    bool isPressed(bool mouseKeyPressed);
};