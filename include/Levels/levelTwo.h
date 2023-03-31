#include <globals.h>

void levelTwo()
{
    switch (currentStage)
    {
        case 1:
            levelTwoStageOne();
            break;
        case 2:
            fadeBetweenStages(2.0f);
            break;
        case 3:
            levelTwoStageTwo();
            break;
        case 4:
            levelTwoStageThree();
            break;
        case 5:
            levelTwoStageFour();
            break;
        case 6:
            levelTwoStageFive();
            break;
        case 7:
            levelTwoStageSix();
            break;
        case 8:
            levelTwoStageSeven();
            break;
        case 9:
            levelTwoStageEight();
            break;
    }
}