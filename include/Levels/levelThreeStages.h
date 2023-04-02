#include <globals.h>

void levelThreeStageOne()
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
            levelThree();
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

void levelThreeStageTwo()
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);
    int flag = 0;

    Vector2 animPos[5] = { 
        856, 263,
        861, 99,
        931, 75,
        1052, 81,
        1084, 208
    }; // Starting position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;
    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans);    

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };

        if (CheckCollisionCircleRec(animPos[0], 15, rect))
        {
            for (int i = 0; i < 5; i++)
            {
                cutAnimation(scalpel, background, animPos[i], animPos[i + 1]);
                ++flag;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(animPos[0], 15, BLUE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageThree()
{
    Texture2D background = LoadTexture("../res/Level3_images/homelander_bald.png");
    Font backwardssans = LoadFontEx("../res/fonts/backwardssans.otf", 64, 0 , 250);

    Vector2 circlePos = {963, 65};
    Vector2 mousePos;
    bool isCircleClicked = 0;
    double distance;

    while (!WindowShouldClose())
    {
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu(); 

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans);    

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
            levelThree();
        }
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();  
}

void levelThreeStageFour()
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
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans);    

        moveTexture(scalpel, position, offset, isDragging);

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos);
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

void levelThreeStageFive()
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
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans);    

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
            levelThree();
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadFont(backwardssans);

    // De-initialization
    CloseWindow();
}

void levelThreeStageSix()
{
    Texture2D background = LoadTexture("../res/Level3_images/fracture.png");
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
        // Handle input
         if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_I))
            displayInfoWindow(background, backwardssans);    

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
            levelThree();
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