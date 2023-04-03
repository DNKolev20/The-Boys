#include <globals.h>

void controls(int selectedItemMenus, float secPosition, bool isMusicPlaying)
{
    Music music = PlayMusic("../res/music/Menu.mp3", secPosition);
    SeekMusicStream(music, secPosition);

    Texture2D background = LoadTexture("../res/background.png");
    Font titleFont = LoadFontEx("../res/fonts/Chopsic.otf", 32, 0 , 250);
    Font buttonFont = LoadFontEx("../res/fonts/molot.otf", 32, 0 , 250);

    int selectedItem = 0;
    int itemsNum = 3;
    const char* itemName[itemsNum] = { "F11 - FullScreen", "I - Info", "Press [Enter] to go back"};

    int itemHeight = 50;
    int itemPadding = 10;
    int itemTextSize = 20;
    int menuWidth = 300;

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        int menuHeight = (itemHeight + itemPadding) * itemsNum - itemPadding - 200;
        int menuX = (screenWidth - menuWidth) / 2;
        int menuY = (screenHeight - menuHeight) / 2;

        Vector2 textSizeTitle = MeasureTextEx(titleFont, "Surgery Simulator", 40, 1);
        Vector2 textPositionTitle = {(screenWidth - textSizeTitle.x) / 2, (screenHeight - textSizeTitle.y) / 2 - 120};

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
        
        DrawTextEx(titleFont, "Surgery Simulator", {(screenWidth - textSizeTitle.x) / 2 - 6, textPositionTitle.y}, 41, 2, WHITE);
        std::vector<LevelData> savefileData = readSaveFile("savefile.txt");
        LevelData& level = savefileData[3];
        if (level.value == true)
            DrawTextEx(titleFont, "Surgery Simulator", textPositionTitle, 40, 2, YELLOW);
        else
            DrawTextEx(titleFont, "Surgery Simulator", textPositionTitle, 40, 2, RED);

        for (int i = 0; i < itemsNum; i++) 
        {
            UpdateMusicStream(music);

            // calculate position and size of item rectangle
            int x = menuX + itemPadding;
            int y = menuY + itemPadding + (itemHeight + itemPadding) * i;
            int width = menuWidth - itemPadding * 2;
            int height = itemHeight;

            // draw item rectangle
            DrawRectangle(x, y, width, height, GRAY);

            // calculate position of item text
            int textWidth = MeasureText(itemName[i], itemTextSize);
            Vector2 textPositionButton = {float(x + (width - textWidth) / 2), float(y + (height - itemTextSize) / 2)};

            // draw item text
            DrawTextEx(buttonFont, itemName[i], textPositionButton, 20, 2, WHITE);
        }

        EndDrawing();

        // Check for button press
        if (IsKeyPressed(KEY_ENTER) && selectedItem >= 0 && selectedItem < itemsNum) {
            // Action to take when Enter key is pressed on selected button
            menu(selectedItemMenus, secPosition, isMusicPlaying);
            return;
        }
    }

    // De-initialization
    CloseWindow();    
}