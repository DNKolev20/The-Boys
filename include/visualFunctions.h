#include <globals.h>

Texture imageloader(const char* path)
{
    Image imageToBeLoaded = LoadImage(path);
    Texture imageToTexture = LoadTextureFromImage(imageToBeLoaded);
    UnloadImage(imageToBeLoaded);

    return imageToTexture;
}