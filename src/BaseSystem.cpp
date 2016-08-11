#include "BaseSystem.h"

#include "Manager.h"
#include "Handle.h"

void ent::BaseSystem::entity_added(ent::EntityID entity_id) {
    if(satisfies(entity_id)) {
        m_entities.push_back(entity_id);
    }
}

void ent::BaseSystem::entity_removed(ent::EntityID entity_id) {
    if(satisfies(entity_id)) {
        m_entities.erase(find_entity(entity_id));
    }
}

void ent::BaseSystem::entity_modified(ent::EntityID entity_id) {
    auto find = find_entity(entity_id);
    if(satisfies(entity_id) && find == m_entities.end()) {
        m_entities.push_back(entity_id);
    } else if(!satisfies(entity_id) && find != m_entities.end()) {
        m_entities.erase(find);
    }
}

bool ent::BaseSystem::satisfies(ent::EntityID entity_id) {
    return (m_filter & m_manager->get_mask(entity_id)) == m_filter;
}

std::vector<ent::EntityID>::iterator ent::BaseSystem::find_entity(ent::EntityID entity_id) {
    return std::find(m_entities.begin(), m_entities.end(), entity_id);
}
