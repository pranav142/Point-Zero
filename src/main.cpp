#include "Game.h"
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include <iostream>

int main() {
    //  shooter::Game game(800, 450);
    //  game.init();
    //  game.run();

    struct Position {
        int x, y;
    };
    struct velocity {
        int x;
    };
    ECS::EntityManager entity_manager;
    ECS::ComponentManager component_manager;

    ECS::Entity entity = entity_manager.create_entity();
    component_manager.add_component<Position>(entity, Position{10, 20});
    auto& position = component_manager.get_component<Position>(entity);
    std::cout << position.x << " " << position.y << std::endl;
}
