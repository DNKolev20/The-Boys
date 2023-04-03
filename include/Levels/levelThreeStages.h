#include <globals.h>

void levelThreeStageOne(Music music, float secPosition, bool isMusicPlaying)
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
            levelThree(music, secPosition, isMusicPlaying);
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

void levelThreeStageTwo(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander.png");
    Texture2D trimmer = LoadTexture("../res/trimmer.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    int flag = 0;

    Vector2 animPos[5] = { 
        { 842, 253 },
        { 844, 102 },
        { 931, 75 },
        { 1052, 81 },
        { 1084, 208 }
    };

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

        moveTexture(trimmer, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)trimmer.width, (float)trimmer.height };

        if (CheckCollisionCircleRec(animPos[0], 10, rect))
        {
            for (int i = 0; i < 4; i++)
            {
                cutAnimation(trimmer, background, animPos[flag], animPos[flag+1], music, secPosition, isMusicPlaying);
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
            levelThree(music, secPosition, isMusicPlaying);
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

void levelThreeStageThree(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_bald.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlePos = { 963, 65 };
    Vector2 mousePos;
    bool isCircleClicked = 0;
    double distance;

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
            levelThree(music, secPosition, isMusicPlaying);
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();  
}

void levelThreeStageFour(Music music, float secPosition, bool isMusicPlaying)
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

void levelThreeStageFive(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_cut.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D retract = LoadTexture("../res/retractor.png");

    Vector2 startPos[2] = {
        { 939, 506 },
        { 979, 506 }
    };

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
            levelThree(music, secPosition, isMusicPlaying);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageSix(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D drill = LoadTexture("../res/drill.png");

    Vector2 circlesPos[4] = {
        { 798, 297 },
        { 990, 285 },
        { 1173, 411 },
        { 1054, 696 }
    }; // Starting positions of the circles

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    bool touchedCircles[4] = { 0, 0, 0, 0 };

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
            levelThree(music, secPosition, isMusicPlaying);
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

void levelThreeStageSeven(Music music, float secPosition, bool isMusicPlaying)
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

        if (CheckCollisionCircleRec(animPos[0], 15, rect))
        {
            for (int i = 0; i < 7; i++)
            {
                cutAnimation(scalpel, background, animPos[flag], animPos[flag+1], music, secPosition, isMusicPlaying);
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
            levelThree(music, secPosition, isMusicPlaying);
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

void levelThreeStageEight(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_holes_cut.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlePos = { 987, 467 };
    Vector2 mousePos;
    bool isCircleClicked = 0;
    double distance;

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
            levelThree(music, secPosition, isMusicPlaying);
        }
 
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageNine(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_no_bone.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D suctionTube = LoadTexture("../res/suction_tube.png");

    Vector2 startPos = { 987, 467 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {
        if (isMusicPlaying)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }
        
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying);

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);       

        moveTexture(suctionTube, position, offset, isDragging);

        // Update image 1
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)suctionTube.width, (float)suctionTube.height }))
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

        Rectangle rect = {position.x, position.y, (float)suctionTube.width, (float)suctionTube.height};

        bool collidesWithCircle = CheckCollisionCircleRec(startPos, 15, rect);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(suctionTube, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);

        if (collidesWithCircle)
        {
            currentStage++;
            levelThree(music, secPosition, isMusicPlaying);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageTen(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_no_bone_1.png");
    
    // Variables to keep track of time and which background image to use
    float timer = 0.0f;
    int backgroundNum = 0;

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying)
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
                levelThree(music, secPosition, isMusicPlaying);
            };   

            char filename[20];
            sprintf(filename, "../res/Level3_images/fracture_no_bone_%d.png", backgroundNum);
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

void levelThreeStageEleven(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_sucked.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D metal = LoadTexture("../res/Level3_images/metal.png");

    Vector2 startPos = { 987, 467 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying);

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);       

        moveTexture(metal, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)metal.width, (float)metal.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            currentStage++;
            levelThree(music, secPosition, isMusicPlaying);
            DrawCircleV(startPos, 15, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

        DrawTexture(metal, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(metal);

    // De-initialization
    CloseWindow();   
}

void levelThreeStageTwelve(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture_metal.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D screw = LoadTexture("../res/screw.png");

    Vector2 circlesPos[4] = {
        {798, 297},
        {990, 276},
        {1182, 411},
        {1054, 698}
    }; // Starting positions of the circles

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    bool touchedCircles[4] = { 0, 0, 0, 0 };

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying)
        {
            secPosition = GetMusicTimePlayed(music);
            UpdateMusicStream(music);
        }

        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(music, secPosition, isMusicPlaying);

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans, music, secPosition, isMusicPlaying);       

        moveTexture(screw, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)screw.width, (float)screw.height };

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

        DrawTexture(screw, position.x, position.y, WHITE);

        if (allCirclesTouched)
        {
            currentStage++;
            levelThree(music, secPosition, isMusicPlaying);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);
    UnloadTexture(screw);

    // De-initialization
    CloseWindow();
}

void levelThreeStageThirteen(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_cut.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    Texture2D needle = LoadTexture("../res/needle.png");

    Vector2 startPos = { 967, 140 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying)
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
            levelThree(music, secPosition, isMusicPlaying);
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

void levelThreeStageFourteen(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/closed_wound_homie.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    while (!WindowShouldClose())
    {   
        if (isMusicPlaying)
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
            levelThree(music, secPosition, isMusicPlaying);
        }
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageFifteen(Music music, float secPosition, bool isMusicPlaying)
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_bald.png");
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
        if (isMusicPlaying)
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
            currentLevel = 1;
            currentStage = 1;
            editLevel("gameCompleted");
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