#ifndef GLOBALS
#define GLOBALS

#include <iostream>
#include <string>
#include <time.h>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "raylib.h"

const float SCREEN_WIDTH = GetScreenWidth();
const float SCREEN_HEIGHT = GetScreenHeight();

void game();
void options();
void menu();

#include "config.h"
#include "visualFunctions.h"
#include "levelFunctions.h"
#include "levels.h"
#include "game.h"
#include "options.h"
#include "menu.h"

#endif