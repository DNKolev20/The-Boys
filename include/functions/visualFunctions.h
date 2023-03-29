#include <globals.h>

void backgroundImage(Texture2D background) 
{
    // Get the current screen size
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calculate the aspect ratio of the texture and the screen
    float textureRatio = (float)background.height / (float)background.width;
    float screenRatio = (float)screenHeight / (float)screenWidth;

    float scale = 1.0f;

    // Determine the scale factor to maintain aspect ratio and fill the screen
    if (textureRatio > screenRatio) 
        scale = (float)screenWidth / (float)background.width;
    else 
        scale = (float)screenHeight / (float)background.height;

    // Calculate the size of the background after scaling
    float textureWidth = background.width * scale;
    float textureHeight = background.height * scale;

    // Calculate the position to center the background on the screen
    float posX = (screenWidth - textureWidth) / 2.0f;
    float posY = (screenHeight - textureHeight) / 2.0f;

    DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
    (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

    if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();
}

void drawMenu(const char* title, int selectedItem, int itemsNum, Color itemColor[], const char* itemName[], Font titleFont, Font buttonFont)
{
    int itemHeight = 50;
    int itemPadding = 10;
    int itemTextSize = 20;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int menuWidth = 300;
    int menuHeight = (itemHeight + itemPadding) * itemsNum - itemPadding - 200;
    int menuX = (screenWidth - menuWidth) / 2;
    int menuY = (screenHeight - menuHeight) / 2;

    Vector2 textSizeTitle = MeasureTextEx(titleFont, title, 40, 1);
    Vector2 textPositionTitle = {(screenWidth - textSizeTitle.x) / 2, (screenHeight - textSizeTitle.y) / 2 - 120};

    DrawTextEx(titleFont, title, {(screenWidth - textSizeTitle.x) / 2 - 6, textPositionTitle.y}, 41, 2, WHITE);
    DrawTextEx(titleFont, title, textPositionTitle, 40, 2, RED);

    for (int i = 0; i < itemsNum; i++) 
    {
        // calculate position and size of item rectangle
        int x = menuX + itemPadding;
        int y = menuY + itemPadding + (itemHeight + itemPadding) * i;
        int width = menuWidth - itemPadding * 2;
        int height = itemHeight;

        // set color of item rectangle based on whether it is selected
        Color color = itemColor[i];
        if (i == selectedItem) {
            color = BLACK;
        }

        // draw item rectangle
        DrawRectangle(x, y, width, height, color);

        // calculate position of item text
        int textWidth = MeasureText(itemName[i], itemTextSize);
        Vector2 textPositionButton = {float(x + (width - textWidth) / 2), float(y + (height - itemTextSize) / 2)};

        // draw item text
        DrawTextEx(buttonFont, itemName[i], textPositionButton, 20, 2, WHITE);
    }
}