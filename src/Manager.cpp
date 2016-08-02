#include "../include/Manager.h"
#include "../include/Handle.h"

ent::Handle ent::Manager::newEntity() {
    ent::Handle handle = createHandle(++nextID_);
    entities_.push_back(handle.id());
    return handle;
}

ent::Handle ent::Manager::createHandle(ent::EntityID entityID) {
    return ent::Handle(this, entityID);
}

ent::Mask& ent::Manager::getMask(ent::EntityID entityID) {
    return entityMaskMap_[entityID];
}

void ent::Manager::removeEntity(ent::EntityID entityID) {
    notifyEntityRemoved(entityID);
    // TODO Recycle ids
    for(auto& comp : entityCompMap_[entityID]) {
        if(comp != nullptr) {
            comp.reset(nullptr);
        }
    }
    entityMaskMap_[entityID].reset();
    entities_.erase(std::find(entities_.begin(), entities_.end(), entityID));
}

void ent::Manager::attach(ent::BaseSystem &system) {
    systems_.push_back(&system);
    system.managerRef_ = this;
    for(auto& entity : entities_) {
        system.entityAdded(entity);
    }
}

void ent::Manager::notifyEntityRemoved(ent::EntityID id) {
    for(auto& system : systems_) {
        system->entityRemoved(id);
    }
}

void ent::Manager::notifyEntityModified(ent::EntityID id) {
    for(auto& system : systems_) {
        system->entityModified(id);
    }
}

void ent::Manager::update(double dt) {
    for(auto& system : systems_) {
        system->update(dt);
    }
}
