#include <globals.h>

void levelOneStageOne(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/patient.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    const char* text[3] = {
        "Hello doctor in training, today your task will be to \noperate on A-Train's heart. [Click Enter to continue]",
        "His heart has been taking a\n heavy toll due to his frequent sprints.\n It will need a replacement. [Click Enter to continue]",
        "Press [I] for more info. \n[Click Enter to continue]"
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
            DrawTextEx(backwardssans, text[tutorial], textPosition[tutorial], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (tutorial == 3)
        {
            currentStage++;
            levelOne(music, secPosition, isMusicPlaying);
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

void levelOneStageTwo(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/stage1_pre-cut.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 startPos = { 967, 140 }; // Starting position of image
    Vector2 endPos = { 951, 939 }; // Ending position of image

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
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos, music, secPosition, isMusicPlaying);
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

void levelOneStageThree(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/cut_wound.png");
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
            levelOne(music, secPosition, isMusicPlaying);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();    
}

void levelOneStageFour(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/open_wound.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D osteotome = LoadTexture("../res/osteotome.png");

    Vector2 circlesPos[3] = {
        {772, 396},
        {794, 563},
        {801, 690}
    }; // Starting positions of the circles

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    bool touchedCircles[3] = {0, 0, 0};

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

        moveTexture(osteotome, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)osteotome.width, (float)osteotome.height };

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        for (int i = 0; i < 3; i++)
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
        for (int i = 0; i < 3; i++)
        {
            if (!touchedCircles[i])
            {
                allCirclesTouched = false;
                break;
            }
        }

        DrawTexture(osteotome, position.x, position.y, WHITE);

        if (allCirclesTouched)
        {
            currentStage++;
            levelOne(music, secPosition, isMusicPlaying);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(osteotome);

    // De-initialization
    CloseWindow();     
}

void levelOneStageFive(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/open_wound_no_bones.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    std::vector<std::vector<Vector2>> cutPositions 
    {{
        {{ /*Start position ->*/ { 823, 439 }, { 888, 420 }   /*<- End position*/   }},
        {{ /*Start position ->*/ { 898, 418 }, { 985, 429 }   /*<- End position*/   }},
        {{ /*Start position ->*/ { 1017, 427 }, { 1076, 425 } /*<- End position*/ }},
        {{ /*Start position ->*/ { 1115, 449 }, { 1121, 505 } /*<- End position*/ }}
    }};

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    int cutVeinArtery = 0;

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

        Rectangle scalpelRect = {position.x, position.y, (float)scalpel.width, (float)scalpel.height};

        // Check for collisions between the image and the circles
        for (auto& positions : cutPositions) {
            for (size_t i = 0; i < positions.size(); i += 2) {
                Vector2 circlePos = positions[i];
                if (CheckCollisionCircleRec(circlePos, 5, scalpelRect)) {
                    // Remove the circle and the corresponding line
                    positions.erase(positions.begin() + i, positions.begin() + i + 2);

                    // Reset the position of the scalpel to {0, 0} when it collides with the circle
                    cutVeinArtery++;

                    cutAnimation(scalpel, background, positions[i], positions[i+1], music, secPosition, isMusicPlaying);
                    position = {0, 0};
                    break;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        for (const auto& positions : cutPositions) {
            for (size_t i = 0; i < positions.size(); i += 2) {
                DrawLineEx(positions[i], positions[i + 1], 5, DARKGRAY);
                DrawCircleV(positions[i], 5, BLUE);
            }
        }

        DrawTexture(scalpel, position.x, position.y, WHITE);

        if (cutVeinArtery == 4)
        {
            currentStage++;
            levelOne(music, secPosition, isMusicPlaying);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();     
}

void levelOneStageSix(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/no_heart.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D heart = LoadTexture("../res/Level1_images/heart.png");

    Vector2 startPos = { 978, 602 };

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

        moveTexture(heart, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)heart.width, (float)heart.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            currentStage++;
            levelOne(music, secPosition, isMusicPlaying);
            DrawCircleV(startPos, 15, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(heart, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(heart);

    // De-initialization
    CloseWindow();   
}

void levelOneStageSeven(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/new_heart.png");
    
    // Variables to keep track of time and which background image to use
    float timer = 0.0f;
    int backgroundNum = 0;

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying == true)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        timer += GetFrameTime();

        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying);

        timer += GetFrameTime();
        
        // If 1.5 seconds have passed, change the background image
        if (timer >= 1.5f)
        {
            // Unload the current background image
            UnloadTexture(background);
            
            // Load the next background image
            backgroundNum++;
            if (backgroundNum > 3)
            {
                currentStage++;
                levelOne(music, secPosition, isMusicPlaying);
            };   

            char filename[20];
            sprintf(filename, "../res/Level1_images/rib%d.png", backgroundNum);
            background = LoadTexture(filename);
            
            // Reset the timer
            timer = 0.0f;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();    
}

void levelOneStageEight(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/rib3.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlesPos[2] = {
        {284, 533},
        {1728, 506},
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
            levelOne(music, secPosition, isMusicPlaying);
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    // De-initialization
    CloseWindow();
}

void levelOneStageNine(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/cut_wound.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D needle = LoadTexture("../res/needle.png");

    Vector2 startPos = { 967, 140 };

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
            levelOne(music, secPosition, isMusicPlaying);
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

void levelOneStageTen(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/closed_wound.png");
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
            levelOne(music, secPosition, isMusicPlaying);
        }
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelOneStageEleven(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level1_images/patient.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    const char* text[2] = {
        "Well done! Performing a heart transplant is\n no easy task. You show promise.\n [Click Enter to continue]",
        "Now head onto Black Noir.\n[Click Enter to continue]",
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
            editLevel("level2");
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