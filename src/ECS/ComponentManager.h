//
// Created by pknadimp on 4/14/25.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <memory>
#include <unordered_map>
#include <typeinfo>

#include "ComponentArray.h"
#include "EntityManager.h"

namespace ECS {
    using ComponentID = size_t;

    class ComponentManager {
    public:
        ComponentManager() {
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            const char *type_name = typeid(T).name();
            if (!m_component_map.contains(type_name)) {
                assert(m_component_count <= MAX_COMPONENTS);
                m_component_map[type_name] = std::make_shared<ComponentArray<T> >();
                m_component_count++;
            }

            std::shared_ptr<ComponentArray<T> > component_array = std::dynamic_pointer_cast<ComponentArray<T> >(
                m_component_map[type_name]);
            component_array->add_component(entity, component);
        };

        template<typename T>
        T &get_component(Entity entity) {
            const char *type_name = typeid(T).name();
            assert(m_component_map.contains(type_name));
            std::shared_ptr<ComponentArray<T> > component_array = std::dynamic_pointer_cast<ComponentArray<T> >(
                m_component_map[type_name]);
            return component_array->get_component(entity);
        }

    private:
        std::unordered_map<const char *, std::shared_ptr<IComponentArray> > m_component_map;
        size_t m_component_count = 0;
    };
}

#endif //COMPONENTMANAGER_H
