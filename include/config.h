#include <globals.h>

void config()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "The Boys");
    SetTargetFPS(60);
    InitAudioDevice();
    SetExitKey(0);
}