#ifndef GLOBALS
#define GLOBALS

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>

#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "raylib/raymath.h"
#include "raylib/raylib.h"

#include "json.hpp"

#include "json/getInfoFromJson.h"

int currentLevel = 1;
int currentStage = 1;

void levelOne();
void levelTwo();
void levelThree();
void menu(int selectedItemMenus);

#include "functions/visualFunctions.h"
#include "Levels/pauseMenu.h"

#include "Levels/functionsForLevels.h"

#include "Levels/levelOneStages.h"
#include "Levels/levelOne.h"

#include "Levels/levelTwoStages.h"
#include "Levels/levelTwo.h"

#include "Levels/levelThreeStages.h"
#include "Levels/levelThree.h"

#include "menus/controls.h"
#include "config.h"
#include "functions/levelFunctions.h"
#include "menus/levelsMenu.h"
#include "game.h"
#include "menus/options.h"
#include "menus/menu.h"

#endif