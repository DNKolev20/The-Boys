#include <globals.h>

void levelOne(Music music, float secPosition, bool isMusicPlaying)
{
    
    switch (currentStage)
    {
        case 1:
            levelOneStageOne(music, secPosition, isMusicPlaying);
            break;
        case 2:
            fadeBetweenStages(2.0f, music, secPosition, isMusicPlaying);
            break;
        case 3:
            levelOneStageTwo(music, secPosition, isMusicPlaying);
            break;
        case 4:
            levelOneStageThree(music, secPosition, isMusicPlaying);
            break;
        case 5:
            levelOneStageFour(music, secPosition, isMusicPlaying);
            break;
        case 6:
            levelOneStageFive(music, secPosition, isMusicPlaying);
            break;
        case 7:
            levelOneStageSix(music, secPosition, isMusicPlaying);
            break;
        case 8:
            levelOneStageSeven(music, secPosition, isMusicPlaying);
            break;
        case 9:
            levelOneStageEight(music, secPosition, isMusicPlaying);
            break;
        case 10:
            levelOneStageNine(music, secPosition, isMusicPlaying);
            break;
        case 11:
            levelOneStageTen(music, secPosition, isMusicPlaying);
            break;
        case 12:
            levelOneStageEleven(music, secPosition, isMusicPlaying);
            break;
    }
}