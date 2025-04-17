//
// Created by pknadimp on 4/14/25.
//

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include <unordered_map>

#include "EntityManager.h"
#include <cassert>

#include "ComponentManager.h"

namespace ECS {
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
    };

    template<typename T>
    class ComponentArray final : public IComponentArray {
    public:
        ComponentArray() = default;

        void add_component(Entity entity, T component) {
            assert(m_entity_to_index.find(entity) == m_entity_to_index.end());

            size_t next_index = m_component_count;
            m_components[next_index] = component;
            m_entity_to_index[entity] = next_index;
            m_index_to_entity[next_index] = entity;
            m_component_count++;
        }

        void remove_component(Entity entity) {
            assert(m_entity_to_index.find(entity) != m_entity_to_index.end());

            // Move the deleted entity to end and erase it
            size_t deleted_index = m_entity_to_index[entity];
            size_t last_index = m_component_count - 1;
            m_components[last_index] = m_components[deleted_index];

            Entity swapped_entity = m_index_to_entity[last_index];
            m_entity_to_index[swapped_entity] = deleted_index;
            m_index_to_entity[deleted_index] = swapped_entity;

            m_entity_to_index.erase(entity);
            m_index_to_entity.erase(last_index);

            m_component_count--;
        }

        T &get_component(Entity entity) {
            assert(m_entity_to_index.find(entity) != m_entity_to_index.end());

            return m_components[m_entity_to_index[entity]];
        }

    private:
        std::array<T, MAX_ENTITIES> m_components;
        std::unordered_map<Entity, size_t> m_entity_to_index;
        std::unordered_map<size_t, Entity> m_index_to_entity;

        int m_component_count = 0;
    };
}


#endif //COMPONENTARRAY_H
