#include <globals.h>

void menu()
{
    int selectedItem = 0;
    int itemsNum = 4;
    Color itemColor[itemsNum] = { GRAY, GRAY, GRAY, GRAY};
    const char* itemName[itemsNum] = { "Play", "Select Levels", "Options", "Exit"};

    while (!WindowShouldClose())
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

        // draw menu items
        DrawButtons(selectedItem, itemsNum, itemColor, itemName);

        EndDrawing();

        // Check for button press
        if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < itemsNum) {
            // Action to take when Enter key is pressed on selected button
            switch (selectedItem) {
                case 0:
                    game();
                    return;
                case 1:
                    levelSelection();
                    return;
                case 2:
                    options();
                    return;
                case 3:
                    CloseWindow();
                    break;
            }
        }        
    }

    // De-initialization
    CloseWindow();
}