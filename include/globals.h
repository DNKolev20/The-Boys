#ifndef GLOBALS
#define GLOBALS

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "raylib.h"

const float SCREEN_WIDTH = GetScreenWidth();
const float SCREEN_HEIGHT = GetScreenHeight();

int currentLevel = 1;

void game();
void options();
void menu();

#include "visualFunctions.h"
#include "Levels/levelOne.h"
#include "Levels/levelTwo.h"
#include "Levels/levelThree.h"

#include "config.h"
#include "levelFunctions.h"
#include "levelsMenu.h"
#include "game.h"
#include "options.h"
#include "menu.h"

#endif