#include "../include/Manager.h"
#include "../include/Handle.h"

ent::Handle ent::Manager::newEntity() {
    ent::Handle handle = createHandle(++nextID);
    entities.push_back(handle.id());
    return handle;
}

ent::Handle ent::Manager::createHandle(ent::EntityID entityID) {
    return ent::Handle(this, entityID);
}

ent::Mask& ent::Manager::getMask(ent::EntityID entityID) {
    return entityMaskMap[entityID];
}

void ent::Manager::removeEntity(ent::EntityID entityID) {
    notifyEntityRemoved(entityID);
    // TODO Recycle ids
    for(auto& comp : entityCompMap[entityID]) {
        if(comp != nullptr) {
            comp.reset(nullptr);
        }
    }
    entityMaskMap[entityID].reset();
    entities.erase(std::find(entities.begin(), entities.end(), entityID));
}

void ent::Manager::attach(ent::BaseSystem &system) {
    systems.push_back(&system);
    system.managerRef = this;
    for(auto& entity : entities) {
        system.entityAdded(entity);
    }
}

void ent::Manager::notifyEntityRemoved(ent::EntityID id) {
    for(auto& system : systems) {
        system->entityRemoved(id);
    }
}

void ent::Manager::notifyEntityModified(ent::EntityID id) {
    for(auto& system : systems) {
        system->entityModified(id);
    }
}

void ent::Manager::update(double dt) {
    for(auto& system : systems) {
        system->update(dt);
    }
}
