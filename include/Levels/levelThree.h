#include <globals.h>

void levelThree(Music music, float secPosition, bool isMusicPlaying)
{
    switch (currentStage)
    {
        case 1:
            levelThreeStageOne(music, secPosition, isMusicPlaying);
            break;
        case 2:
            fadeBetweenStages(2.0f, music, secPosition, isMusicPlaying);
            break;
        case 3:
            levelThreeStageTwo(music, secPosition, isMusicPlaying);
            break;
        case 4:
            levelThreeStageThree(music, secPosition, isMusicPlaying);
            break;
        case 5:
            levelThreeStageFour(music, secPosition, isMusicPlaying);
            break;
        case 6:
            levelThreeStageFive(music, secPosition, isMusicPlaying);
            break;
        case 7:
            levelThreeStageSix(music, secPosition, isMusicPlaying);
            break;
        case 8:
            levelThreeStageSeven(music, secPosition, isMusicPlaying);
            break;
        case 9:
            levelThreeStageEight(music, secPosition, isMusicPlaying);
            break;
    }
}