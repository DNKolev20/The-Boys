#include <globals.h>

using json = nlohmann::json;

std::vector<std::string> loadItemNames(int levelNum, int stageNum)
{
    std::vector<std::string> itemNames;
    
    // Load JSON file
    std::ifstream file("info.json");
    json data;
    file >> data;
    
    // Get the specified level and stage
    auto levels = data["levels"];
    auto& level = levels[levelNum];
    auto& stage = level["stages"][stageNum];
    
    // Get names for each item in the stage
    for (auto& item : stage["items"]) {
        std::string name = item["name"];
        itemNames.push_back(name);
    }
    
    return itemNames;
}

std::vector<std::string> loadItemDescription(int levelNum, int stageNum)
{
    std::vector<std::string> itemDescription;
    
    // Load JSON file
    std::ifstream file("info.json");
    json data;
    file >> data;
    
    // Get the specified level and stage
    auto levels = data["levels"];
    auto& level = levels[levelNum];
    auto& stage = level["stages"][stageNum];
    
    // Get names for each item in the stage
    for (auto& item : stage["items"]) {
        std::string name = item["description"];
        itemDescription.push_back(name.c_str());
    }
    
    return itemDescription;
}


std::vector<Texture2D> loadTextures(int levelNum, int stageNum)
{
    std::vector<Texture2D> textures;
    
    // Load JSON file
    std::ifstream file("info.json");
    json data;
    file >> data;
    
    // Get the specified level and stage
    auto levels = data["levels"];
    auto& level = levels[levelNum];
    auto& stage = level["stages"][stageNum];

    for (auto& item : stage["items"]) {
    std::string imagePath = item["imagePath"];
    if (imagePath == "none") {
        textures.push_back({0});
    } else {
        // Load the texture from the image path and push it to the vector
        Texture2D texture = LoadTexture(imagePath.c_str());
        textures.push_back(texture);
    }
}

    
    return textures;
}