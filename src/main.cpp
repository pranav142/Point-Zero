#include "Game.h"
#include <iostream>

#include "ECS/Registry.h"

int main() {
    shooter::Game game(800, 450);
    game.init();
    game.run();
}
