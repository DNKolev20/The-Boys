#include <globals.h>

void game(int selectedItemMenus, bool isMusicPlaying)
{
    Music music;

    switch(currentLevel)
    {
        case 1:
            music = PlayMusic("../res/music/LevelOne.mp3", 1.0f);
            break;
        case 2:
            music = PlayMusic("../res/music/LevelTwo.mp3", 1.0f);
            break;
        case 3:
            music = PlayMusic("../res/music/LevelThree.mp3", 1.0f);
            break;
    }

    switch(currentLevel)
    {
        case 1:
            levelOne(music, 1.0f, isMusicPlaying);
            return;
        case 2:
            levelTwo(music, 1.0f, isMusicPlaying);
            return;
        case 3:
            levelThree(music, 1.0f, isMusicPlaying);
            return;
    }
}