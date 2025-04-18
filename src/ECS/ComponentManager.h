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
        ComponentManager() = default;

        ~ComponentManager() = default;

        template<typename T>
        ComponentID add_component(Entity entity, T component) {
            auto component_array = get_component_array<T>(true);
            component_array->add(entity, component);
            return get_component_id<T>();
        };

        template<typename T>
        T &get_component(Entity entity) {
            auto component_array = get_component_array<T>(false);
            return component_array->get(entity);
        }

        template<typename T>
        ComponentID remove_component(Entity entity) {
            auto component_array = get_component_array<T>(false);
            component_array->remove(entity);
            return get_component_id<T>();
        }

        void destroy_entity(Entity entity) {
            for (auto &[type_name, component_array]: m_component_map) {
                component_array->destroy(entity);
            }
        }

    private:
        // Create flag specifies whether to create the component array if not found
        template<typename T>
        std::shared_ptr<ComponentArray<T> > get_component_array(bool create) {
            const char *type_name = typeid(T).name();
            assert(m_component_map.contains(type_name) || create);

            if (!m_component_map.contains(type_name) && create) {
                assert(m_next_component_id <= MAX_COMPONENTS);
                m_component_map[type_name] = std::make_shared<ComponentArray<T> >();
                m_name_to_id[type_name] = m_next_component_id++;
            }

            return std::static_pointer_cast<ComponentArray<T> >(m_component_map[type_name]);
        }

        template<typename T>
        ComponentID get_component_id() {
            const char *type_name = typeid(T).name();
            assert(m_name_to_id.contains(type_name));
            return m_name_to_id[type_name];
        }

    private:
        std::unordered_map<const char *, std::shared_ptr<IComponentArray> > m_component_map;
        std::unordered_map<const char *, ComponentID> m_name_to_id;

        size_t m_next_component_id = 0;
    };
}

#endif //COMPONENTMANAGER_H
