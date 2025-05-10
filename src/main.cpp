#include "Game.h"
#include <iostream>

#include "ECS/Registry.h"

int main() {
    shooter::Game game(1280, 720);
    game.init();
    game.run();
}
