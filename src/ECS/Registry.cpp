//
// Created by pknadimp on 4/17/25.
//

#include "Registry.h"

namespace ECS {
    Entity Registry::create() {
        return m_entity_manager.create();
    }

    void Registry::destroy(Entity entity) {
        m_component_manager.destroy_entity(entity);
        m_entity_manager.destroy(entity);
    }

    void Registry::add_component_id(Entity entity, ComponentID id) {
        ComponentMask mask = m_entity_manager.get_component_mask(entity);
        mask.set(id, true);
        m_entity_manager.set_component_mask(entity, mask);
    }

    void Registry::remove_component_id(Entity entity, ComponentID id) {
        ComponentMask mask = m_entity_manager.get_component_mask(entity);
        mask.set(id, false);
        m_entity_manager.set_component_mask(entity, mask);
    }
} // ECS
