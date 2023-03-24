#include <globals.h>

int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Boys");
    
    SetTargetFPS(60);    
    menu(); // starts the game
    return 0;
}