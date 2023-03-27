#include <globals.h>

void game(int selectedItemMenus)
{
   switch(currentLevel)
    {
        case 1:
            levelOne();
            return;
        case 2:
            levelTwo();
            return;
        case 3:
            levelThree();
            return;
    }
}