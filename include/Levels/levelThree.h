#include <globals.h>

void levelThree()
{
    switch (currentStage)
    {
        case 1:
            levelThreeStageOne();
            break;
        case 2:
            fadeBetweenStages(2.0f);
            break;
        case 3:
            levelThreeStageTwo();
            break;
        case 4:
            levelThreeStageThree();
            break;
        case 5:
            levelThreeStageFour();
            break;
        case 6:
            levelThreeStageFive();
            break;
        case 7:
            levelThreeStageSix();
            break;
        case 8:
            levelThreeStageSeven();
            break;
        case 9:
            levelThreeStageEight();
            break;
    }
}