#include <globals.h>

void pauseMenu() 
{
    int selectedItem = 0;
    int itemsNum = 4;
    Color itemColor[itemsNum] = { GRAY, GRAY, GRAY, GRAY};
    const char* itemName[itemsNum] = { "Fullscreen","Resume", "Main Menu","Exit Game"};
    bool isPaused = false;

    while (!WindowShouldClose()) 
    {
        if (IsKeyPressed(KEY_ESCAPE)) {
            isPaused = !isPaused;
        }

        if (isPaused) 
        {

            // handle user input
            if (IsKeyPressed(KEY_UP)) {
                selectedItem--;
                if (selectedItem < 0) {
                    selectedItem = itemsNum - 1;
                }
            }
            else if (IsKeyPressed(KEY_DOWN)) {
                selectedItem++;
                if (selectedItem >= itemsNum) {
                    selectedItem = 0;
                }
            }

            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("PAUSE MENU", GetScreenWidth() / 2 - MeasureText("PAUSE MENU", 40) / 2, GetScreenHeight() / 2 - 60, 40, BLACK);

            // draw menu items
            DrawButtons(selectedItem, itemsNum, itemColor, itemName, false);
    
            EndDrawing();
            // Check for button press
            if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < itemsNum) {
                // Action to take when Enter key is pressed on selected button
                switch (selectedItem) {
                    case 0:
                        ToggleFullscreen();
                        break;
                    case 1:
                        isPaused = false;
                        break;
                    case 2:
                        menu(0);
                        return;
                    case 3:
                        CloseWindow();
                        break;
                }
            }
        }
        else{ break; }
    }
}