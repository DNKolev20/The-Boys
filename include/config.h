#include <globals.h>

void config()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Boys");
    SetTargetFPS(60);
    SetExitKey(0);

}