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

int currentLevel = 1;
int currentStage = 1;

void levelOne();
void levelTwo();
void levelThree();
void menu();

#include "visualFunctions.h"
#include "Levels/pauseMenu.h"

#include "Levels/functionsForLevels.h"

#include "Levels/levelOneStages.h"
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