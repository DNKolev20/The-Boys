#include <globals.h>

void levelThree(Music music, float secPosition)
{
    switch (currentStage)
    {
        case 1:
            levelThreeStageOne(music, secPosition);
            break;
        case 2:
            fadeBetweenStages(2.0f, music, secPosition);
            break;
        case 3:
            levelThreeStageTwo(music, secPosition);
            break;
        case 4:
            levelThreeStageThree(music, secPosition);
            break;
        case 5:
            levelThreeStageFour(music, secPosition);
            break;
        case 6:
            levelThreeStageFive(music, secPosition);
            break;
        case 7:
            levelThreeStageSix(music, secPosition);
            break;
        case 8:
            levelThreeStageSeven(music, secPosition);
            break;
        case 9:
            levelThreeStageEight(music, secPosition);
            break;
    }
}