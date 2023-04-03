#include <globals.h>

void levelOne(Music music, float secPosition)
{
    
    switch (currentStage)
    {
        case 1:
            levelOneStageOne(music, secPosition);
            break;
        case 2:
            fadeBetweenStages(2.0f, music, secPosition);
            break;
        case 3:
            levelOneStageTwo(music, secPosition);
            break;
        case 4:
            levelOneStageThree(music, secPosition);
            break;
        case 5:
            levelOneStageFour(music, secPosition);
            break;
        case 6:
            levelOneStageFive(music, secPosition);
            break;
        case 7:
            levelOneStageSix(music, secPosition);
            break;
        case 8:
            levelOneStageSeven(music, secPosition);
            break;
        case 9:
            levelOneStageEight(music, secPosition);
            break;
        case 10:
            levelOneStageNine(music, secPosition);
            break;
        case 11:
            levelOneStageTen(music, secPosition);
            break;
        case 12:
            levelOneStageEleven(music, secPosition);
            break;
    }
}