#include "Game.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {

    int amountOfLife = stoi(argv[1]);
    int damageLevel = stoi(argv[2]);
    const string inputFile = argv[3];
    Game game{inputFile, amountOfLife, damageLevel};

    game.initializer();
    game.run();

    return 0;
}
