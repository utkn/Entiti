#include "Manager.h"
#include "Handle.h"

ent::Handle ent::Manager::new_entity() {
    ent::Handle handle = create_handle(++m_next_entity_id);
    m_entities.push_back(handle.get_id());
    return handle;
}

ent::Handle ent::Manager::create_handle(ent::EntityID entityID) {
    return ent::Handle(this, entityID);
}

ent::Mask& ent::Manager::get_mask(ent::EntityID entityID) {
    return m_entity_mask_map[entityID];
}

void ent::Manager::remove_entity(ent::EntityID entityID) {
    notify_entity_removed(entityID);
    // TODO Recycle ids
    for(auto& comp : m_entity_comp_map[entityID]) {
        if(comp != nullptr) {
            comp.reset(nullptr);
        }
    }
    m_entity_mask_map[entityID].reset();
    m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entityID));
}

void ent::Manager::attach_system(ent::BaseSystem& system) {
    m_systems.emplace_back(&system);
    system.m_manager = this;
    system.createFilter();
    for(auto& entity : m_entities) {
        system.entity_added(entity);
    }
}

void ent::Manager::notify_entity_removed(ent::EntityID id) {
    for(auto& system : m_systems) {
        system->entity_removed(id);
    }
}

void ent::Manager::notify_entity_modified(ent::EntityID id) {
    for(auto& system : m_systems) {
        system->entity_modified(id);
    }
}

void ent::Manager::update(double dt) {
    for(auto& system : m_systems) {
        system->update(dt);
    }
}
