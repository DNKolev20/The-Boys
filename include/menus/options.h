#include <globals.h>

void options()
{
    int selectedItem = 0;
    int itemsNum = 2;
    Color itemColor[itemsNum] = { GRAY, GRAY};
    const char* itemName[itemsNum] = { "Fullscreen", "Back"};

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

        if (IsKeyPressed(KEY_ESCAPE))
        {
            menu();
            return;            
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        // draw menu items
        DrawButtons(selectedItem, itemsNum, itemColor, itemName, true);

        EndDrawing();

        // Check for button press
        if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < itemsNum) {
            // Action to take when Enter key is pressed on selected button
            switch (selectedItem) {
                case 0:
                    ToggleFullscreen();
                    break;
                case 1:
                    menu();
                    return;
            }
        }
    }

    // De-initialization
    CloseWindow();
}