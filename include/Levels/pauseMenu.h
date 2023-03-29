#include <globals.h>

void pauseMenu() 
{
    Texture2D background = LoadTexture("../res/background.png");
    Font titleFont = LoadFont("../res/fonts/Chopsic.otf");
    Font buttonFont = LoadFontEx("../res/fonts/molot.otf", 32, 0 , 250);

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

            backgroundImage(background);

            ClearBackground(RAYWHITE);

            // DrawTextEx(titleFont, "PAUSE MENU", {(float)GetScreenWidth() / 2 - MeasureText("PAUSE MENU", 40) / 2 - 22, (float)GetScreenHeight() / 2 - 60}, 41, 2, WHITE);
            // DrawTextEx(titleFont, "PAUSE MENU", {(float)GetScreenWidth() / 2 - MeasureText("PAUSE MENU", 40) / 2 - 19, (float)GetScreenHeight() / 2 - 60}, 40, 2, RED);

            // draw menu items
            drawMenu("PAUSE MENU", selectedItem, itemsNum, itemColor, itemName, titleFont, buttonFont);
    
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