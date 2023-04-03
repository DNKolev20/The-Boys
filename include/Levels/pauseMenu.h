#include <globals.h>

void pauseMenu(Music music, float secPosition, bool isMusicPlaying) 
{
    Texture2D background = LoadTexture("../res/background.png");
    Font titleFont = LoadFont("../res/fonts/Chopsic.otf");
    Font buttonFont = LoadFontEx("../res/fonts/molot.otf", 32, 0 , 250);

    int selectedItem = 0;
    int itemsNum = 5;
    Color itemColor[itemsNum] = { GRAY, GRAY, GRAY, GRAY, GRAY};
    const char* itemName[itemsNum] = { "Resume","Mute Music","FullScreen", "Main Menu","Exit Game"};
    bool isPaused = true;

    while (!WindowShouldClose()) 
    {
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

            // draw menu items
            drawMenu("PAUSE MENU", selectedItem, itemsNum, itemColor, itemName, titleFont, buttonFont);
    
            EndDrawing();

            // Check for button press
            if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < itemsNum) {
                // Action to take when Enter key is pressed on selected button
                switch (selectedItem) {
                    case 0:
                        isPaused = false;
                        break;
                    case 1:
                        if (isMusicPlaying)
                            isMusicPlaying = false;
                        else
                            isMusicPlaying = true;
                        break;
                    case 2:
                        ToggleFullscreen();
                        break;
                    case 3:
                        menu(0, 1.0f, isMusicPlaying);
                        return;
                    case 4:
                        CloseWindow();
                        break;
                }
            }
        }
        else
        {
            switch(currentLevel)
            {
                case 1:
                    levelOne(music, secPosition, isMusicPlaying);
                    return;
                case 2:
                    levelTwo(music, secPosition, isMusicPlaying);
                    return;
                case 3:
                    levelThree(music, secPosition, isMusicPlaying);
                    return;
            }
        }
    }
}