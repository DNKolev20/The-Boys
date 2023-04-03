#include <globals.h>

void levelTwo(Music music, float secPosition)
{
    switch (currentStage)
    {
        case 1:
            levelTwoStageOne(music, secPosition);
            break;
        case 2:
            fadeBetweenStages(2.0f, music, secPosition);
            break;
        case 3:
            levelTwoStageTwo(music, secPosition);
            break;
        case 4:
            levelTwoStageThree(music, secPosition);
            break;
        case 5:
            levelTwoStageFour(music, secPosition);
            break;
        case 6:
            levelTwoStageFive(music, secPosition);
            break;
        case 7:
            levelTwoStageSix(music, secPosition);
            break;
        case 8:
            levelTwoStageSeven(music, secPosition);
            break;
        case 9:
            levelTwoStageEight(music, secPosition);
            break;
    }
}