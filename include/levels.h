#include <globals.h>

void levelSelection()
{
    Texture2D levelTexture = LoadTexture("../res/testImg.png");
    Texture2D levelTexture2 = LoadTexture("../res/testImg.png");
    Texture2D levelTexture3 = LoadTexture("../res/testImg.png");

     // Define the colors to be used for the squares
    Color squareColor = GRAY;
    Color textColor = WHITE;
    int selectedSquare = 0;
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        const int squareSize = GetScreenHeight() / 3.5;
        const int squareSpacing = GetScreenWidth() / 10;
        const int totalWidth = squareSize * 3 + squareSpacing * 2;
        const int startX = (GetScreenWidth() - totalWidth) / 2;
        const int startY = (GetScreenHeight() - squareSize) / 2;
        const Rectangle square1 = { startX, startY, squareSize, squareSize };
        const Rectangle square2 = { startX + squareSize + squareSpacing, startY, squareSize, squareSize };
        const Rectangle square3 = { startX + squareSize * 2 + squareSpacing * 2, startY, squareSize, squareSize };

        // Calculate text sizes and positions
        const char* text1 = "Level 1";
        const char* text2 = "Level 2";
        const char* text3 = "Level 3";
        const int textHeight = GetScreenHeight() / 20;
        const int textWidth1 = MeasureText(text1, textHeight);
        const int textWidth2 = MeasureText(text2, textHeight);
        const int textWidth3 = MeasureText(text3, textHeight);
        const int textStartX1 = square1.x + (squareSize - textWidth1) / 2;
        const int textStartX2 = square2.x + (squareSize - textWidth2) / 2;
        const int textStartX3 = square3.x + (squareSize - textWidth3) / 2;
        const int textY = startY + squareSize + GetScreenHeight() / 20;

        // Calculate back button size and position on the screen
        const char* backButton = "Back";
        const int backButtonHeight = GetScreenHeight() / 25;
        const int backButtonWidth = MeasureText(backButton, backButtonHeight);
        const int backButtonX = (GetScreenWidth() - backButtonWidth) / 2;
        const int backButtonY = textY + GetScreenHeight() / 10;
        const int backButtonPadding = backButtonHeight / 2;
        const Rectangle backButtonRec = {
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

        DrawRectangleRec(square1, selectedSquare == 0 ? GREEN : BLUE);
        DrawRectangleRec(square2, selectedSquare == 1 ? GREEN : BLUE);
        DrawRectangleRec(square3, selectedSquare == 2 ? GREEN : BLUE);
        DrawRectangleRec(backButtonRec, selectedSquare == 3 ? GREEN : GRAY);

        DrawText(text1, textStartX1, textY, textHeight, BLACK);
        DrawText(text2, textStartX2, textY, textHeight, BLACK);
        DrawText(text3, textStartX3, textY, textHeight, BLACK);
        DrawText(backButton, backButtonX, backButtonY, backButtonHeight, WHITE);

        Vector2 texturePos = {
        square1.x + (square1.width - levelTexture.width) / 2,
        square1.y + (square1.height - levelTexture.height) / 2
        };
        DrawTexture(levelTexture, texturePos.x, texturePos.y, WHITE);

        texturePos = {
            square2.x + (square2.width - levelTexture2.width) / 2,
            square2.y + (square2.height - levelTexture2.height) / 2
        };
        DrawTexture(levelTexture2, texturePos.x, texturePos.y, WHITE);

        texturePos = {
            square3.x + (square3.width - levelTexture3.width) / 2,
            square3.y + (square3.height - levelTexture3.height) / 2
        };
        DrawTexture(levelTexture3, texturePos.x, texturePos.y, WHITE);

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