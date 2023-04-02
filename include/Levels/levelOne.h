#include <globals.h>

void levelOne()
{
    
    switch (currentStage)
    {
        case 1:
            levelOneStageOne();
            break;
        case 2:
            fadeBetweenStages(2.0f);
            break;
        case 3:
            levelOneStageTwo();
            break;
        case 4:
            levelOneStageThree();
            break;
        case 5:
            levelOneStageFour();
            break;
        case 6:
            levelOneStageFive();
            break;
        case 7:
            levelOneStageSix();
            break;
        case 8:
            levelOneStageSeven();
            break;
        case 9:
            levelOneStageEight();
            break;
        case 10:
            levelOneStageNine();
            break;
        case 11:
            levelOneStageTen();
            break;
        case 12:
            levelOneStageEleven();
            break;
    }
}