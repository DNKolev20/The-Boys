#include <globals.h>

void drawSelectPanel(Rectangle squares[], int selectedSquare, int MAX_TEXTURES)
{
    for (int i = 0; i < MAX_TEXTURES; i++)
        DrawRectangleRec(squares[i], selectedSquare == i ? BLACK : GRAY);
}

void drawTextForPanels(const char* text[], float textStartX[], float textY, float textHeight, int MAX_TEXTURES)
{
    for (int i = 0; i < MAX_TEXTURES; i++)
        DrawText(text[i], textStartX[i], textY, textHeight, BLACK);
}