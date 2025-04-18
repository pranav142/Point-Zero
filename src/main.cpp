#include "Game.h"
#include <iostream>

#include "ECS/Registry.h"

int main() {
    shooter::Game game(800, 450);
    game.init();
    game.run();

    // struct Position {
    //     int x, y;
    // };
    // struct Velocity {
    //     int x;
    // };

    // ECS::Registry m_registry;
    // ECS::Entity entity = m_registry.create();
    // m_registry.add_component<Position>(entity, {0, 0});
    // m_registry.add_component<Velocity>(entity, {10});

    // auto velocity = m_registry.get_component<Velocity>(entity);
    // auto position = m_registry.get_component<Position>(entity);

    // std::cout << position.x << ", " << position.y << std::endl;
    // std::cout << velocity.x << std::endl;
}
