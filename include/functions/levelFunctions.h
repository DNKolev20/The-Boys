#include <globals.h>

struct LevelData {
    std::string name;
    bool value;
};

void drawSelectPanel(Rectangle squares[], int selectedSquare, int MAX_TEXTURES)
{
    for (int i = 0; i < MAX_TEXTURES; i++)
        DrawRectangleRec(squares[i], selectedSquare == i ? BLACK : GRAY);
}

void drawTextForPanels(const char* text[], float textStartX[], float textY, float textHeight, int MAX_TEXTURES)
{
    for (int i = 0; i < MAX_TEXTURES; i++)
        DrawText(text[i], textStartX[i], textY, textHeight, BLACK);
}

std::vector<LevelData> readSaveFile(const std::string& filename)
{
    std::vector<LevelData> data;
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line))
    {
        // split the line into a name and value
        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) continue;
        std::string name = line.substr(0, eq_pos);
        bool value = (line[eq_pos + 2] == '1');

        // create a LevelData object and add it to the vector
        data.push_back({name, value});
    }

    return data;
}

Texture2D checkUnlocked(Texture2D levelTextures[])
{
    std::vector<LevelData> savefileData = readSaveFile("savefile.txt");

    for (int i = 0; i < 3; i++)
    {
        LevelData& level = savefileData[i];
        if (level.value)
            levelTextures[i] = LoadTexture("../res/testImg.png");
        else
            levelTextures[i] = LoadTexture("../res/locked.png");
    }
        

    return *levelTextures;
}

bool isUnlocked(int level)
{
    std::vector<LevelData> savefileData = readSaveFile("savefile.txt");

    if (level == 4) return true;

    return savefileData[level-1].value == true ? 1 : 0;
}