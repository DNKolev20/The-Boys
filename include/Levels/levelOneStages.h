#include <globals.h>

extern int currentStage;

void stageOne()
{
    Texture2D background = LoadTexture("../res/Level1_images/patient.png");
    const char* text[3] = {
        "Hello doctor in training, today your task will be to \noperate A-Train's heart. [Click Enter to continue]",
        "You will be given instruments for the operation.\n[Click Enter to continue]",
        "You will be guided by your mentor.\n[Click Enter to continue]"
    };
    
    const int fontSize = 32;
    
    Vector2 textSize[3];
    Vector2 textPosition[3];

    for (int i = 0; i < 3; i++)
        textSize[i] = MeasureTextEx(GetFontDefault(), text[i], fontSize, 2.0f);

    for (int i = 0; i < 3; i++)
        textPosition[i] = {GetScreenWidth()/2 - textSize[i].x/2, GetScreenHeight() - textSize[i].y - 200};

    int tutorial = 0;

    while (!WindowShouldClose())
    {    
        // Get the current screen size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the aspect ratio of the texture and the screen
        float textureRatio = (float)background.height / (float)background.width;
        float screenRatio = (float)screenHeight / (float)screenWidth;

        float scale = 1.0f;

        // Determine the scale factor to maintain aspect ratio and fill the screen
        if (textureRatio > screenRatio) 
        {
            scale = (float)screenHeight / (float)background.height;
        }
        else 
        {
            scale = (float)screenWidth / (float)background.width;
        }

        // Calculate the size of the background after scaling
        float textureWidth = background.width * scale;
        float textureHeight = background.height * scale;

        // Calculate the position to center the background on the screen
        float posX = (screenWidth - textureWidth) / 2.0f;
        float posY = (screenHeight - textureHeight) / 2.0f;

        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();    
        }

        // Draw
        BeginDrawing();

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        if (tutorial != 3)
            DrawTextEx(GetFontDefault(), text[tutorial], textPosition[tutorial], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (tutorial == 3)
        {
            currentStage++;
            levelOne();
        }

        if (IsKeyPressed(KEY_ENTER) && tutorial < 3)
            tutorial++;
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}

void stageTwo()
{
    Texture2D background = LoadTexture("../res/Level1_images/stage1_pre-cut.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    Vector2 startPos = { 967, 140 }; // Starting position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        // Get the current screen size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the aspect ratio of the texture and the screen
        float textureRatio = (float)background.height / (float)background.width;
        float screenRatio = (float)screenHeight / (float)screenWidth;

        float scale = 1.0f;

        // Determine the scale factor to maintain aspect ratio and fill the screen
        if (textureRatio > screenRatio) 
        {
            scale = (float)screenHeight / (float)background.height;
        }
        else 
        {
            scale = (float)screenWidth / (float)background.width;
        }

        // Calculate the size of the background after scaling
        float textureWidth = background.width * scale;
        float textureHeight = background.height * scale;

        // Calculate the position to center the background on the screen
        float posX = (screenWidth - textureWidth) / 2.0f;
        float posY = (screenHeight - textureHeight) / 2.0f;

        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();    
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)scalpel.width, (float)scalpel.height }))
            {
                offset = Vector2Subtract(mousePosition, position);
                isDragging = true;
            }
        }

        if (isDragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            position = Vector2Subtract(mousePosition, offset);
        }
        else
        {
            isDragging = false;
        }

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            startCutting();
            DrawCircleV(startPos, 15, BLUE);
        }
        else
        {
            DrawCircleV(startPos, 15, RED);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, RED);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}

void stageThree()
{
    Texture2D background = LoadTexture("../res/Level1_images/cut_wound.png");

    Texture2D retracts[2] = {
        LoadTexture("../res/retractor.png"),
        LoadTexture("../res/retractor.png")
    };

    Vector2 startPos[2] = {
        { 939, 506 },
        { 979, 506 }
    };

    Vector2 position[2] = {
        {0, 0},
        {0, 0}
    };

    Vector2 offset[2] = {
        {0, 0},
        {0, 0}
    };

    bool isDragging[2] = {0, 0};

    while (!WindowShouldClose())
    {
        // Get the current screen size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the aspect ratio of the texture and the screen
        float textureRatio = (float)background.height / (float)background.width;
        float screenRatio = (float)screenHeight / (float)screenWidth;

        float scale = 1.0f;

        // Determine the scale factor to maintain aspect ratio and fill the screen
        if (textureRatio > screenRatio) 
            scale = (float)screenHeight / (float)background.height;
        else 
            scale = (float)screenWidth / (float)background.width;

        // Calculate the size of the background after scaling
        float textureWidth = background.width * scale;
        float textureHeight = background.height * scale;

        // Calculate the position to center the background on the screen
        float posX = (screenWidth - textureWidth) / 2.0f;
        float posY = (screenHeight - textureHeight) / 2.0f;


        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();    
        }

        for (int i = 0; i < 2; i++)
        {
            // Update image 1
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, { position[i].x, position[i].y, (float)retracts[i].width, (float)retracts[i].height }))
                {
                    offset[i] = Vector2Subtract(mousePosition, position[i]);
                    isDragging[i] = true;
                }
            }

            if (isDragging[i] && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePosition = GetMousePosition();
                position[i] = Vector2Subtract(mousePosition, offset[i]);
            }
            else
            {
                isDragging[i] = false;
            } 
        }           

        Rectangle rects[2] = {
            { position[0].x, position[0].y, (float)retracts[0].width, (float)retracts[0].height },
            { position[1].x, position[1].y, (float)retracts[1].width, (float)retracts[1].height }
        };

        bool collidesWithCircle = CheckCollisionCircleRec(startPos[0], 15, rects[0]) && CheckCollisionCircleRec(startPos[1], 15, rects[1]);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        for (int i = 0; i < 2; i++)
            DrawTexture(retracts[i], position[i].x, position[i].y, WHITE);
        

        DrawCircleV(startPos[0], 15, RED);
        DrawCircleV(startPos[1], 15, RED);

        if (collidesWithCircle)
        {
            currentStage++;
            levelOne();
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();    
}

void stageFour()
{
    Texture2D background = LoadTexture("../res/Level1_images/open_wound.png");

    while (!WindowShouldClose())
    {
        // Get the current screen size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the aspect ratio of the texture and the screen
        float textureRatio = (float)background.height / (float)background.width;
        float screenRatio = (float)screenHeight / (float)screenWidth;

        float scale = 1.0f;

        // Determine the scale factor to maintain aspect ratio and fill the screen
        if (textureRatio > screenRatio) 
            scale = (float)screenHeight / (float)background.height;
        else 
            scale = (float)screenWidth / (float)background.width;

        // Calculate the size of the background after scaling
        float textureWidth = background.width * scale;
        float textureHeight = background.height * scale;

        // Calculate the position to center the background on the screen
        float posX = (screenWidth - textureWidth) / 2.0f;
        float posY = (screenHeight - textureHeight) / 2.0f;


        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();    
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            std::cout << GetMousePosition().x << " " << GetMousePosition().y;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);


        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();     
}