#include <globals.h>

using json = nlohmann::json;

int main() 
{
    config();

    menu(0); // starts the game
    return 0;
}