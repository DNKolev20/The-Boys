#include <globals.h>

void menu(int selectedItemMenus, float secPosition, bool isMusicPlaying)
{
    Music music = PlayMusic("../res/music/Menu.mp3", secPosition);
    SeekMusicStream(music, secPosition);

    Texture2D background = LoadTexture("../res/background.png");
    Font titleFont = LoadFontEx("../res/fonts/Chopsic.otf", 32, 0 , 250);
    Font buttonFont = LoadFontEx("../res/fonts/molot.otf", 32, 0 , 250);

    int selectedItem = selectedItemMenus;
    int itemsNum = 5;
    Color itemColor[itemsNum] = { GRAY, GRAY, GRAY, GRAY,GRAY};
    const char* itemName[itemsNum] = { "Play", "Select Levels", "Options", "Controls", "Exit"};

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

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

        // draw menu items
        drawMenu("Surgery Simulator", selectedItem, itemsNum, itemColor, itemName, titleFont, buttonFont);

        EndDrawing();

        // Check for button press
        if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < itemsNum) {
            // Action to take when Enter key is pressed on selected button
            switch (selectedItem) {
                case 0:

                    game(selectedItem, isMusicPlaying);
                    return;
                case 1:
                    levelSelection(selectedItem, secPosition, isMusicPlaying);
                    return;
                case 2:
                    options(selectedItem, secPosition, isMusicPlaying);
                    return;
                case 3:
                    controls(selectedItem, secPosition, isMusicPlaying);
                    return;
                case 4:
                    CloseWindow();
                    break;
            }
        }        
    }

    UnloadTexture(background);
    UnloadMusicStream(music);

    // De-initialization
    CloseWindow();
}