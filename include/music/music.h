#include <globals.h>

Music PlayMusic(const char* musicPath, float secPosition)
{
    Music music = LoadMusicStream(musicPath);
    PlayMusicStream(music);
    SetMusicVolume(music, 0.1f);
    return music;
}