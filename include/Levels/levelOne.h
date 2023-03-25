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
            break;
        case 5:
            stageFour();
            break;
    }
}