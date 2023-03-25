#include <globals.h>

void levelSelection()
{
    int MAX_TEXTURES = 3;

    Texture2D levelTextures[MAX_TEXTURES] = {
        LoadTexture("../res/testImg.png"),
        LoadTexture("../res/testImg.png"),
        LoadTexture("../res/testImg.png")
    };

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

    while (!WindowShouldClose()) 
    {
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
        float backButtonWidth = MeasureText(backButton, backButtonHeight);
        float backButtonX = (GetScreenWidth() - backButtonWidth) / 2;
        float backButtonY = textY + GetScreenHeight() / 10;
        float backButtonPadding = backButtonHeight / 2;
        Rectangle backButtonRec = {
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

        // Draw squares and text
        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawSelectPanel(squares, selectedSquare, MAX_TEXTURES);

        DrawRectangleRec(backButtonRec, selectedSquare == 3 ? BLACK : squareColor);

        drawTextForPanels(text, textStartX, textY, textHeight, MAX_TEXTURES);
        DrawText(backButton, backButtonX, backButtonY, backButtonHeight, textColor);

        for (int i = 0; i < MAX_TEXTURES; i++)
        {
            texturePos = {
                squares[i].x + (squares[i].width - levelTextures[i].width) / 2,
                squares[i].y + (squares[i].width - levelTextures[i].width) / 2
            };

            DrawTexture(levelTextures[i], texturePos.x, texturePos.y, textColor);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER) && selectedSquare >= 0 && selectedSquare <= 3)
        {
            switch (selectedSquare) {
                case 0:
                    std::cout << 0 << std::endl;
                case 1:
                    std::cout << 1 << std::endl;
                case 2:
                    std::cout << 2 << std::endl;
                case 3:
                    menu();
                    return;

            }
        }
    }
    CloseWindow();
}