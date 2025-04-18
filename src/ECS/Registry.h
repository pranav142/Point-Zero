//
// Created by pknadimp on 4/17/25.
//

#ifndef REGISTRY_H
#define REGISTRY_H

#include "EntityManager.h"
#include "ComponentManager.h"

namespace ECS {
    class Registry {
    public:
        Entity create();

        void destroy(Entity entity);

        template<typename T>
        void add_component(Entity entity, T component) {
            ComponentID id = m_component_manager.add_component(entity, component);
            add_component_id(entity, id);
        }

        template<typename T>
        T &get_component(Entity entity) {
            return m_component_manager.get_component<T>(entity);
        }

        template<typename T>
        void remove_component(Entity entity) {
            ComponentID id = m_component_manager.remove_component<T>(entity);
            remove_component_id(entity, id);
        }

    private:
        void add_component_id(Entity entity, ComponentID id);

        void remove_component_id(Entity entity, ComponentID id);

    private:
        EntityManager m_entity_manager;
        ComponentManager m_component_manager;
    };
}

#endif //REGISTRY_H
