#include <globals.h>

void levelSelection(int selectedItemMenus, float secPosition, bool isMusicPlaying)
{
    Music music = PlayMusic("../res/music/Menu.mp3", secPosition);
    SeekMusicStream(music, secPosition);

    Texture2D background = LoadTexture("../res/background.png");
    Font font = LoadFontEx("../res/fonts/futura.ttf", 32, 0 , 250);

    int MAX_TEXTURES = 3;

    Texture2D levelTextures[MAX_TEXTURES];

    *levelTextures = checkUnlocked(levelTextures);

     // Define the colors to be used for the squares
    Color squareColor = GRAY;
    Color textColor = WHITE;
    int selectedSquare = 0;

    const char* text[3] = {
        "Level 1",
        "Level 2",
        "Level 3"
    };

    float textWidth[3];
    float textStartX[3];

    Vector2 texturePos;

    switch (currentLevel)
    {
        case 1:
            selectedSquare = 0;
            break;
        case 2:
            selectedSquare = 1;
            break;
        case 3:
            selectedSquare = 2;
            break;
    }

    while (!WindowShouldClose()) 
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        float squareSize = GetScreenHeight() / 3.5;
        float squareSpacing = GetScreenWidth() / 10;
        float totalWidth = squareSize * 3 + squareSpacing * 2;
        float startX = (GetScreenWidth() - totalWidth) / 2;
        float startY = (GetScreenHeight() - squareSize) / 2;

        Rectangle squares[3] {
            /* Element 1*/ {startX, startY, squareSize, squareSize},
            /* Element 2*/ {startX + squareSize + squareSpacing, startY, squareSize, squareSize},
            /* Element 3*/ {startX + squareSize * 2 + squareSpacing * 2, startY, squareSize, squareSize }
        };

        float textHeight = GetScreenHeight() / 20;

        for (int i = 0; i < 3; i++)
            textWidth[i] = MeasureText(text[i], textHeight);

        for (int i = 0; i < 3; i++)
            textStartX[i] = squares[i].x + (squareSize - textWidth[i]) / 2;

        float textY = startY + squareSize + GetScreenHeight() / 20;

        // Calculate back button size and position on the screen
        const char* backButton = "Back";
        float backButtonHeight = GetScreenHeight() / 25;
        float backButtonWidth = MeasureText(backButton, backButtonHeight) + 10;
        float backButtonX = (GetScreenWidth() - backButtonWidth) / 2;
        float backButtonY = textY + GetScreenHeight() / 10;
        float backButtonPadding = backButtonHeight / 2;
        Rectangle backButtonRec = 
        {
            backButtonX - backButtonPadding,
            backButtonY - backButtonPadding,
            backButtonWidth + backButtonPadding * 2,
            backButtonHeight + backButtonPadding * 2
        };

        // Update the selected square index based on arrow key input
        if (IsKeyPressed(KEY_LEFT))
        {
            selectedSquare--;
            if (selectedSquare < 0) selectedSquare = 2;
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            selectedSquare++;
            if (selectedSquare > 2) selectedSquare = 0;
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            selectedSquare = 3;
        }
        else if (IsKeyPressed(KEY_UP) && selectedSquare == 3)
        {
            selectedSquare = 0;
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            
            menu(selectedItemMenus, secPosition, isMusicPlaying);
            return;            
        }

        // Draw squares and text
        BeginDrawing();

        backgroundImage(background);

        ClearBackground(RAYWHITE);

        drawSelectPanel(squares, selectedSquare, MAX_TEXTURES);

        DrawRectangleRec(backButtonRec, selectedSquare == 3 ? BLACK : squareColor);

        drawTextForPanels(text, textStartX, textY, textHeight, MAX_TEXTURES, font);

        DrawTextEx(font, backButton, {backButtonX, backButtonY}, backButtonHeight, 2, textColor);

        for (int i = 0; i < MAX_TEXTURES; i++)
        {
            texturePos = {
                squares[i].x + (squares[i].width - levelTextures[i].width) / 2,
                squares[i].y + (squares[i].width - levelTextures[i].width) / 2
            };

            DrawTexture(levelTextures[i], texturePos.x, texturePos.y, textColor);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER) && selectedSquare >= 0 && selectedSquare <= 3 && isUnlocked(selectedSquare+1))
        {
            switch (selectedSquare) 
            {
                case 0:
                    currentLevel = 1;
                    currentStage = 1;
                    menu(selectedItemMenus, secPosition, isMusicPlaying);
                    return;
                case 1:
                    currentLevel = 2;
                    currentStage = 1;
                    menu(selectedItemMenus, secPosition, isMusicPlaying);
                    return;
                case 2:
                    currentLevel = 3;
                    currentStage = 1;
                    menu(selectedItemMenus, secPosition, isMusicPlaying);
                    return;
                case 3:
                    menu(selectedItemMenus, secPosition, isMusicPlaying);
                    return;

            }
        }
    }
    // Unload textures
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(levelTextures[i]);
    }


    CloseWindow();
}