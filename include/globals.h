#ifndef GLOBALS
#define GLOBALS

#include <iostream>
#include <string>
#include <time.h>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "raylib.h"

#define MAX_TEXTURES 2

const float SCREEN_WIDTH = GetScreenWidth();
const float SCREEN_HEIGHT = GetScreenHeight();

void game();
void options();
void menu();

#include "visualFunctions.h"
#include "game.h"
#include "options.h"
#include "menu.h"

#endif