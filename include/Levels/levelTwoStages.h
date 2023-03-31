#include <globals.h>

void levelTwoStageOne()
{
    Texture2D background = LoadTexture("../res/Level2_images/patient.png");
    Font font = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    const char* text[3] = {
        "Hello doctor in training, today your task will be to \noperate Black Noir's appendix. [Click Enter to continue]",
        "You will be given instruments for the operation.\n[Click Enter to continue]",
        "You will be guided by your mentor.\n[Click Enter to continue]"
    };
    
    const int fontSize = 48;
    
    Vector2 textSize[3];
    Vector2 textPosition[3];

    for (int i = 0; i < 3; i++)
        textSize[i] = MeasureTextEx(font, text[i], fontSize, 2.0f);

    for (int i = 0; i < 3; i++)
        textPosition[i] = {GetScreenWidth()/2 - textSize[i].x/2, GetScreenHeight() - textSize[i].y - 200};

    int tutorial = 0;

    while (!WindowShouldClose())
    {    
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();    

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        if (tutorial != 3)
            DrawTextEx(font, text[tutorial], textPosition[tutorial], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (tutorial == 3)
        {
            currentStage++;
            levelTwo();
        }

        if (IsKeyPressed(KEY_ENTER) && tutorial < 3)
            tutorial++;
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}

void levelTwoStageTwo()
{
    Texture2D background = LoadTexture("../res/Level2_images/stage1_pre_cut.png");
    const Texture2D& scalpel = LoadTexture("../res/scalpel.png");

    Vector2 startPos = { 976, 240 }; // Starting position of image
    Vector2 endPos = { 973, 766 }; // Ending position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();    

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 10, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos);
            DrawCircleV(startPos, 10, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(startPos, 10, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}

void levelTwoStageThree()
{
    Texture2D background = LoadTexture("../res/Level2_images/cut_wound.png");

    Texture2D retract = LoadTexture("../res/retractor.png");

    Vector2 startPos[2] = {
        { 939, 506 },
        { 979, 506 }
    };

    Vector2 position = {0, 0};
    Vector2 offset = {0, 0};
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();    

        moveTexture(retract, position, offset, isDragging);

        // Update image 1
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)retract.width, (float)retract.height }))
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
            isDragging = false;

        Rectangle rect = {position.x, position.y, (float)retract.width, (float)retract.height};

        bool collidesWithCircle = CheckCollisionCircleRec(startPos[0], 10, rect) && CheckCollisionCircleRec(startPos[1], 10, rect);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(retract, position.x, position.y, WHITE);    

        for (int i = 0; i < 2; i++)
            DrawCircleV(startPos[i], 10, BLUE);

        if (collidesWithCircle)
        {
            currentStage++;
            levelTwo();
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}

void levelTwoStageFour()
{
    Texture2D background = LoadTexture("../res/Level2_images/open_wound.png");
    const Texture2D& scalpel = LoadTexture("../res/scalpel.png");

    Vector2 startPos = { 950, 641 }; // Starting position of image
    Vector2 endPos = { 984, 609 }; // Ending position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();    

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 10, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos);
            DrawCircleV(startPos, 10, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(startPos, 10, BLUE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}

void levelTwoStageFive()
{
    Texture2D background = LoadTexture("../res/Level2_images/removed_appendicitis_with_retractors.png");

    Vector2 circlesPos[2] = {
        {1370, 247},
        {499, 708},
    }; // Starting positions of the circles
    Vector2 mousePos;
    bool isCircleClicked[2] = {0, 0};
    double distance[2];

    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        mousePos = GetMousePosition();
        distance[0] = sqrt(pow(mousePos.x - circlesPos[0].x, 2) + pow(mousePos.y - circlesPos[0].y, 2));
        distance[1] = sqrt(pow(mousePos.x - circlesPos[1].x, 2) + pow(mousePos.y - circlesPos[1].y, 2));    

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        for (int i = 0; i < 2; i++)
        {
            if (distance[i] < 10 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                isCircleClicked[i] = true;
            else if (isCircleClicked[i])
                DrawCircleV(circlesPos[i], 10, GREEN);
            else
                DrawCircleV(circlesPos[i], 10, BLUE);

        }

        if (isCircleClicked[0] == 1 && isCircleClicked[1] == 1)
        {
            currentStage++;
            levelTwo();
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    // De-initialization
    CloseWindow();
}

void levelTwoStageSix()
{
    Texture2D background = LoadTexture("../res/Level2_images/removed_appendicitis.png");
    Texture2D needle = LoadTexture("../res/needle.png");

    Vector2 startPos = { 943, 402 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();    

        moveTexture(needle, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)needle.width, (float)needle.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            currentStage++;
            levelTwo();
            DrawCircleV(startPos, 15, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(needle, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(needle);

    // De-initialization
    CloseWindow();
}

void levelTwoStageSeven()
{
    Texture2D background = LoadTexture("../res/Level2_images/closed_wound.png");

    while (!WindowShouldClose())
    {
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();    

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTextEx(GetFontDefault(), "Press [Enter] to continue", {(float)GetScreenWidth()/2 - 200, (float)GetScreenHeight() - 232}, 32, 2.0f, BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
        {
            menu(0);
        }
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}