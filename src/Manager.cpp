#include "../include/Manager.h"
#include "../include/Handle.h"

ent::Handle ent::Manager::newEntity() {
    ent::Handle handle = createHandle(++m_nextEntityID);
    m_entities.push_back(handle.getID());
    return handle;
}

ent::Handle ent::Manager::createHandle(ent::EntityID entityID) {
    return ent::Handle(this, entityID);
}

ent::Mask& ent::Manager::getMask(ent::EntityID entityID) {
    return m_entityMaskMap[entityID];
}

void ent::Manager::removeEntity(ent::EntityID entityID) {
    notifyEntityRemoved(entityID);
    // TODO Recycle ids
    for(auto& comp : m_entityCompMap[entityID]) {
        if(comp != nullptr) {
            comp.reset(nullptr);
        }
    }
    m_entityMaskMap[entityID].reset();
    m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entityID));
}

void ent::Manager::attachSystem(ent::BaseSystem& system) {
    m_systems.emplace_back(&system);
    system.m_managerRef = this;
    for(auto& entity : m_entities) {
        system.entityAdded(entity);
    }
}

void ent::Manager::notifyEntityRemoved(ent::EntityID id) {
    for(auto& system : m_systems) {
        system->entityRemoved(id);
    }
}

void ent::Manager::notifyEntityModified(ent::EntityID id) {
    for(auto& system : m_systems) {
        system->entityModified(id);
    }
}

void ent::Manager::update(double dt) {
    for(auto& system : m_systems) {
        system->update(dt);
    }
}
