#include <globals.h>

void levelTwoStageOne(Music music, float secPosition, bool isMusicPlaying)
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
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
          if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying); 

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
            levelTwo(music, secPosition, isMusicPlaying);
        }

        if (IsKeyPressed(KEY_ENTER) && tutorial < 3)
            tutorial++;
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}

void levelTwoStageTwo(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/stage1_pre_cut.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    Vector2 startPos = { 976, 240 }; // Starting position of image
    Vector2 endPos = { 973, 766 }; // Ending position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying); 

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);        

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 10, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos, music, secPosition, isMusicPlaying);
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
    UnloadFont(backwardssans);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}

void levelTwoStageThree(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/cut_wound.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D retractor = LoadTexture("../res/retractor.png");

    Vector2 startPos[2] = {
        { 939, 506 },
        { 979, 506 }
    };

    Vector2 position = {0, 0};
    Vector2 offset = {0, 0};
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
          if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying); 

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);   

        moveTexture(retractor, position, offset, isDragging);

        // Update image 1
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)retractor.width, (float)retractor.height }))
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

        Rectangle rect = {position.x, position.y, (float)retractor.width, (float)retractor.height};

        bool collidesWithCircle = CheckCollisionCircleRec(startPos[0], 10, rect) && CheckCollisionCircleRec(startPos[1], 10, rect);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(retractor, position.x, position.y, WHITE);    

        for (int i = 0; i < 2; i++)
            DrawCircleV(startPos[i], 10, BLUE);

        if (collidesWithCircle)
        {
            currentStage++;
            levelTwo(music, secPosition, isMusicPlaying);
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(retractor);

    // De-initialization
    CloseWindow();
}

void levelTwoStageFour(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/open_wound.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    Vector2 startPos = { 950, 641 }; // Starting position of image
    Vector2 endPos = { 984, 609 }; // Ending position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying); 

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);       

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 10, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos, music, secPosition, isMusicPlaying);
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
    UnloadFont(backwardssans);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}

void levelTwoStageFive(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/removed_appendicitis_with_retractors.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlesPos[2] = {
        {1370, 247},
        {499, 708},
    }; // Starting positions of the circles
    Vector2 mousePos;
    bool isCircleClicked[2] = {0, 0};
    double distance[2];

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying); 

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);   

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
            levelTwo(music, secPosition, isMusicPlaying);
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelTwoStageSix(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/removed_appendicitis.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D needle = LoadTexture("../res/needle.png");

    Vector2 startPos = { 943, 402 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }
        // Handle input
          if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying); 

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);   

        moveTexture(needle, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)needle.width, (float)needle.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            currentStage++;
            levelTwo(music, secPosition, isMusicPlaying);
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
    UnloadFont(backwardssans);
    UnloadTexture(needle);

    // De-initialization
    CloseWindow();
}

void levelTwoStageSeven(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/closed_wound.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
          if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying);   

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTextEx(backwardssans, "Press [Enter] to continue", {(float)GetScreenWidth()/2 - 200, (float)GetScreenHeight() - 232}, 32, 2.0f, BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
        {
            currentStage++;
            levelTwo(music, secPosition, isMusicPlaying);
        }
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelTwoStageEight(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level2_images/patient.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    const char* text[2] = {
        "Well done! You're on your way to become an excellent surgeon!\n [Click Enter to continue]",
        "Now head onto the next patient.\n[Click Enter to continue]",
    };
    
    const int fontSize = 48;
    
    Vector2 textSize[2];
    Vector2 textPosition[2];

    for (int i = 0; i < 2; i++)
        textSize[i] = MeasureTextEx(backwardssans, text[i], fontSize, 2.0f);

    for (int i = 0; i < 2; i++)
        textPosition[i] = {GetScreenWidth()/2 - textSize[i].x/2, GetScreenHeight() - textSize[i].y - 200};

    int end = 0;

    while (!WindowShouldClose())
    {
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
          if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying);  

        // Draw
        BeginDrawing();

        backgroundImage(background);

        if (end != 2)
            DrawTextEx(backwardssans, text[end], textPosition[end], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (end == 2)
        {
            currentLevel++;
            currentStage = 1;
            editLevel("level3");
            menu(0, 1.0f, isMusicPlaying);
        }

        if (IsKeyPressed(KEY_ENTER) && end < 3)
            end++;
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}