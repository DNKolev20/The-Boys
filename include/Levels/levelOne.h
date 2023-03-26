#include <globals.h>

void levelOne()
{

    switch (currentStage)
    {
        case 1:
            stageOne();
            break;
        case 2:
            fadeBetweenStages(2.0f);
            break;
        case 3:
            stageTwo();
            break;
        case 4:
            stageThree();
            break;
        case 5:
            stageFour();
            break;
        case 6:
            stageFive();
            break;
        case 7:
            stageSix();
            break;
        case 8:
            stageSeven();
            break;
        case 9:
            stageEight();
            break;
        case 10:
            stageNine();
            break;
        case 11:
            stageTen();
            break;
    }
}