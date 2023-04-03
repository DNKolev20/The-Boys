#include <globals.h>

void levelTwo(Music music, float secPosition, bool isMusicPlaying)
{
    switch (currentStage)
    {
        case 1:
            levelTwoStageOne(music, secPosition, isMusicPlaying);
            break;
        case 2:
            fadeBetweenStages(2.0f, music, secPosition, isMusicPlaying);
            break;
        case 3:
            levelTwoStageTwo(music, secPosition, isMusicPlaying);
            break;
        case 4:
            levelTwoStageThree(music, secPosition, isMusicPlaying);
            break;
        case 5:
            levelTwoStageFour(music, secPosition, isMusicPlaying);
            break;
        case 6:
            levelTwoStageFive(music, secPosition, isMusicPlaying);
            break;
        case 7:
            levelTwoStageSix(music, secPosition, isMusicPlaying);
            break;
        case 8:
            levelTwoStageSeven(music, secPosition, isMusicPlaying);
            break;
        case 9:
            levelTwoStageEight(music, secPosition, isMusicPlaying);
            break;
    }
}