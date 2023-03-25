#include <globals.h>

void DrawButtons(int selectedItem, int itemsNum, Color itemColor[], const char* itemName[], bool showtitle)
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

    if (showtitle)
    {
        int titleY = menuY + itemPadding - 150;
        DrawText("Surgery simulator", menuX + itemPadding - 30, titleY, 40, BLACK);
    }

    for (int i = 0; i < itemsNum; i++) {
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
        int textX = x + (width - textWidth) / 2;
        int textY = y + (height - itemTextSize) / 2;

        // draw item text
        DrawText(itemName[i], textX, textY, itemTextSize, WHITE);
    }
}