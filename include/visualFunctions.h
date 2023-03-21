#include <globals.h>

Vector2 texturePositions[MAX_TEXTURES] = {0};

// Check which texture has been clicked
int CheckTextureClick(Texture2D textures[], int count)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < count; i++)
        {
            if (CheckCollisionPointRec(mousePos, (Rectangle){texturePositions[i].x, texturePositions[i].y, textures[i].width, textures[i].height}))
            {
                return i; // Texture i has been clicked
            }
        }
    }
    return -1; // No texture has been clicked
}

// Move the specified texture
void MoveTexture(Vector2 *position)
{
    Vector2 mouseDelta = GetMouseDelta();

    // Add mouse delta to texture position
    position->x += mouseDelta.x;
    position->y += mouseDelta.y;
}