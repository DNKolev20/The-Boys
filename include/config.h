#include <globals.h>

void config()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "The Boys");
    SetTargetFPS(60);
    SetExitKey(0);
}