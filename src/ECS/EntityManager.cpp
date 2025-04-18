//
// Created by pknadimp on 4/14/25.
//

#include "EntityManager.h"

#include <cassert>

ECS::Entity ECS::EntityManager::create() {
    assert(m_entity_count <= MAX_ENTITIES);

    Entity entity = m_unused_entities.front();
    m_unused_entities.pop();
    m_entity_count++;
    return entity;
}

void ECS::EntityManager::destroy(Entity entity) {
    assert(entity < MAX_ENTITIES);

    m_unused_entities.push(entity);
    m_component_masks[entity].reset();
    m_entity_count--;
}

void ECS::EntityManager::set_component_mask(Entity entity, ComponentMask mask) {
    assert(entity < MAX_ENTITIES);
    m_component_masks[entity] = mask;
}

ECS::ComponentMask ECS::EntityManager::get_component_mask(Entity entity) const {
    assert(entity < MAX_ENTITIES);

    return m_component_masks[entity];
}
