#include <globals.h>

Vector2 texturePositions[MAX_TEXTURES] = {0};
    const int NUM_ITEMS = 3; // number of items in the menu
    const int ITEM_HEIGHT = 50; // height of each item
    const int ITEM_PADDING = 10; // padding between items
    const int ITEM_TEXT_SIZE = 20; // font size for item text
    const int ITEM_TEXT_PADDING = 15; // padding around item text
    const Color ITEM_COLOR[NUM_ITEMS] = { GREEN, RED, BLUE}; // colors for each item
    const char* ITEM_NAME[NUM_ITEMS] = { "Play", "Select Levels", "Options"}; // names for each item

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

void DrawMenuItems(int selectedItem) 
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int menuWidth = 300;
    int menuHeight = (ITEM_HEIGHT + ITEM_PADDING) * NUM_ITEMS - ITEM_PADDING - 200;
    int menuX = (screenWidth - menuWidth) / 2;
    int menuY = (screenHeight - menuHeight) / 2;

    int titleY = menuY + ITEM_PADDING - 150;
    DrawText("The Boys", menuX + ITEM_PADDING + 35, titleY, 40, BLACK);

    for (int i = 0; i < NUM_ITEMS; i++) {
        // calculate position and size of item rectangle
        int x = menuX + ITEM_PADDING;
        int y = menuY + ITEM_PADDING + (ITEM_HEIGHT + ITEM_PADDING) * i;
        int width = menuWidth - ITEM_PADDING * 2;
        int height = ITEM_HEIGHT;

        // set color of item rectangle based on whether it is selected
        Color color = ITEM_COLOR[i];
        if (i == selectedItem) {
            color = PURPLE;
        }

        // draw item rectangle
        DrawRectangle(x, y, width, height, color);

        // calculate position of item text
        int textWidth = MeasureText(ITEM_NAME[i], ITEM_TEXT_SIZE);
        int textX = x + (width - textWidth) / 2;
        int textY = y + (height - ITEM_TEXT_SIZE) / 2;

        // draw item text
        DrawText(ITEM_NAME[i], textX, textY, ITEM_TEXT_SIZE, WHITE);
    }
}