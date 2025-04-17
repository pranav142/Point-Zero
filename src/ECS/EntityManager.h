//
// Created by pknadimp on 4/14/25.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <array>
#include <bitset>
#include <cstdint>
#include <queue>

namespace ECS {
    constexpr size_t MAX_COMPONENTS = 32;
    constexpr size_t MAX_ENTITIES = 500;

    using Entity = uint32_t;
    using ComponentMask = std::bitset<MAX_COMPONENTS>;

    class EntityManager {
    public:
        EntityManager() {
            for (int i = 0; i < MAX_ENTITIES; i++) {
                m_unused_entities.push(i);
            }
        }

        Entity create_entity();

        void delete_entity(Entity entity);

        void set_component_mask(Entity entity, ComponentMask mask);

        ComponentMask get_component_mask(Entity entity) const;

    private:
        std::queue<Entity> m_unused_entities;
        std::array<ComponentMask, MAX_ENTITIES> m_component_masks;

        int m_entity_count = 0;
    };
}


#endif //ENTITYMANAGER_H
