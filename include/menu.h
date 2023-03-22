#include <globals.h>

void menu()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Boys");
    
    SetTargetFPS(60);

    int selectedItem = 0;

    while (!WindowShouldClose())
    {
        // handle user input
        if (IsKeyPressed(KEY_UP)) {
            selectedItem--;
            if (selectedItem < 0) {
                selectedItem = NUM_ITEMS - 1;
            }
        }
        else if (IsKeyPressed(KEY_DOWN)) {
            selectedItem++;
            if (selectedItem >= NUM_ITEMS) {
                selectedItem = 0;
            }
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

          // draw menu items
        DrawMenuItems(selectedItem);

        // Check for button press
        if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < NUM_ITEMS) {
            // Action to take when Enter key is pressed on selected button
            switch (selectedItem) {
                case 0:
                    game();
                    return;
                case 1:
                    std::cout << 2 << std::endl;
                    break;
                case 2:
                    std::cout << 3 << std::endl;
                    break;
                case 3:
                    std::cout << 4 << std::endl;
                    break;
            }
        }

        EndDrawing();
    }

    // De-initialization
    CloseWindow();
}