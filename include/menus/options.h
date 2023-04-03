#include <globals.h>

void options(int selectedItemMenus, float secPosition, bool isMusicPlaying)
{
    Music music = PlayMusic("../res/music/Menu.mp3", secPosition);
    SeekMusicStream(music, secPosition);

    Texture2D background = LoadTexture("../res/background.png");
    Font titleFont = LoadFontEx("../res/fonts/Chopsic.otf", 32, 0 , 250);
    Font buttonFont = LoadFontEx("../res/fonts/molot.otf", 32, 0 , 250);

    int selectedItem = 0;
    int itemsNum = 3;
    Color itemColor[itemsNum] = { GRAY, GRAY, GRAY};
    const char* itemName[itemsNum] = { "Mute Music","Fullscreen", "Back"};

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

        if (IsKeyPressed(KEY_ESCAPE))
        {
            menu(selectedItemMenus, secPosition, isMusicPlaying);
            return;            
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
                    if (isMusicPlaying)
                        isMusicPlaying = false;
                    else
                        isMusicPlaying = true;
                    break;
                case 1:
                    ToggleFullscreen();
                    break;
                case 2:
                    menu(selectedItemMenus, secPosition, isMusicPlaying);
                    return;
            }
        }
    }

    // De-initialization
    CloseWindow();
}