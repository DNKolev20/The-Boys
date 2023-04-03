#include <globals.h>

void levelThreeStageOne(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    const char* text[3] = {
        "Hello doctor in training, today your task will be to \noperate Homelander's brain. [Click Enter to continue]",
        "You will be given instruments for the operation.\n[Click Enter to continue]",
        "You will be guided by your mentor.\n[Click Enter to continue]"
    };
    
    const int fontSize = 48;
    
    Vector2 textSize[3];
    Vector2 textPosition[3];

    for (int i = 0; i < 3; i++)
        textSize[i] = MeasureTextEx(backwardssans, text[i], fontSize, 2.0f);

    for (int i = 0; i < 3; i++)
        textPosition[i] = {GetScreenWidth()/2 - textSize[i].x/2, GetScreenHeight() - textSize[i].y - 200};

    int tutorial = 0;

    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 

        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        if (tutorial != 3)
            DrawTextEx(backwardssans, text[tutorial], textPosition[tutorial], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (tutorial == 3)
        {
            currentStage++;
            levelThree(music, secPosition);
        }

        if (IsKeyPressed(KEY_ENTER) && tutorial < 3)
            tutorial++;
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();    
}

void levelThreeStageTwo(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander.png");
    Texture2D trimmer = LoadTexture("../res/trimmer.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    int flag = 0;

    Vector2 animPos[5] = { 
        {842, 253},
        {844, 102},
        {931, 75},
        {1052, 81},
        {1084, 208}
    };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };

    bool isDragging = false;

    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition);       

        moveTexture(trimmer, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)trimmer.width, (float)trimmer.height };

        if (CheckCollisionCircleRec(animPos[0], 10, rect))
        {
            for (int i = 0; i < 4; i++)
            {
                cutAnimation(trimmer, background, animPos[flag], animPos[flag+1], music, 1.0f);
                flag++;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        DrawTexture(trimmer, position.x, position.y, WHITE);

        DrawCircleV(animPos[0], 10, BLUE);

        if (flag == 4)
        {
            currentStage++;
            levelThree(music, secPosition);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(trimmer);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageThree(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_bald.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlePos = {963, 65};
    Vector2 mousePos;
    bool isCircleClicked = 0;
    double distance;

    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(); 

        mousePos = GetMousePosition();
        distance = sqrt(pow(mousePos.x - circlePos.x, 2) + pow(mousePos.y - circlePos.y, 2));   

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        if (distance < 10 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            isCircleClicked = true;
        else if (isCircleClicked)
            DrawCircleV(circlePos, 10, GREEN);
        else
            DrawCircleV(circlePos, 10, BLUE);

        if (isCircleClicked == 1)
        {
            currentStage++;
            levelThree(music, secPosition);
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();  
}

void levelThreeStageFour(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_head.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 startPos = { 967, 140 }; // Starting position of image
    Vector2 endPos = { 951, 939 }; // Ending position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;
    
    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition);       

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos, music, 1.0f);
            DrawCircleV(startPos, 15, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageFive(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_cut.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
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
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition);       

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

        bool collidesWithCircle = CheckCollisionCircleRec(startPos[0], 15, rect) && CheckCollisionCircleRec(startPos[1], 15, rect);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(retract, position.x, position.y, WHITE);    

        for (int i = 0; i < 2; i++)
            DrawCircleV(startPos[i], 15, BLUE);

        if (collidesWithCircle)
        {
            currentStage++;
            levelThree(music, secPosition);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageSix(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D drill = LoadTexture("../res/drill.png");

    Vector2 circlesPos[4] = {
        {798, 297},
        {990, 285},
        {1173, 411},
        {1054, 696}
    }; // Starting positions of the circles

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    bool touchedCircles[4] = {0, 0, 0, 0};

    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition);       

        moveTexture(drill, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)drill.width, (float)drill.height };

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        for (int i = 0; i < 4; i++)
        {
            if (CheckCollisionCircleRec(circlesPos[i], 15, rect))
            {
                DrawCircleV(circlesPos[i], 15, GREEN);
                touchedCircles[i] = true;
            }
            else
                DrawCircleV(circlesPos[i], 15, touchedCircles[i] ? GREEN : BLUE);

        }
        
        bool allCirclesTouched = true;
        for (int i = 0; i < 4; i++)
        {
            if (!touchedCircles[i])
            {
                allCirclesTouched = false;
                break;
            }
        }

        DrawTexture(drill, position.x, position.y, WHITE);

        if (allCirclesTouched)
        {
            currentStage++;
            levelThree(music, secPosition);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(drill);

    // De-initialization
    CloseWindow();
}

void levelThreeStageSeven(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_holes.png");
    Texture2D scalpel = LoadTexture("../res/bonesaw.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    int flag = 0;

    Vector2 animPos[8] = { 
        {798, 297},
        {990, 285},
        {1173, 411},
        {1054, 696},
        {982, 624},
        {880, 606},
        {794, 468},
        {798, 297}
    };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };

    bool isDragging = false;

    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music); 
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition);       

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };

        if (CheckCollisionCircleRec(animPos[0], 15, rect))
        {
            for (int i = 0; i < 7; i++)
            {
                cutAnimation(scalpel, background, animPos[flag], animPos[flag+1], music, 1.0f);
                flag++;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(animPos[0], 15, BLUE);

        if (flag == 7)
        {
            currentStage++;
            levelThree(music, secPosition);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageEight(Music music, float secPosition)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_holes_cut.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlePos = {987, 467};
    Vector2 mousePos;
    bool isCircleClicked = 0;
    double distance;

    while (!WindowShouldClose())
    {
        secPosition = GetMusicTimePlayed(music);
        UpdateMusicStream(music);
        
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(); 

        mousePos = GetMousePosition();
        distance = sqrt(pow(mousePos.x - circlePos.x, 2) + pow(mousePos.y - circlePos.y, 2));   

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        if (distance < 10 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            isCircleClicked = true;
        else if (isCircleClicked)
            DrawCircleV(circlePos, 10, GREEN);
        else
            DrawCircleV(circlePos, 10, BLUE);

        if (isCircleClicked == 1)
        {
            currentStage++;
            levelThree(music, secPosition);
        }
 
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

