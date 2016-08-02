#include "../include/BaseSystem.h"

#include "../include/Manager.h"
#include "../include/Handle.h"

void ent::BaseSystem::entityAdded(ent::EntityID entityID) {
    if(satisfies(entityID)) {
        entities_.push_back(managerRef_->createHandle(entityID));
    }
}

void ent::BaseSystem::entityRemoved(ent::EntityID entityID) {
    if(satisfies(entityID)) {
        entities_.erase(findEntity(entityID));
    }
}

void ent::BaseSystem::entityModified(ent::EntityID entityID) {
    auto find = findEntity(entityID);
    if(satisfies(entityID) && find == entities_.end()) {
        entities_.push_back(managerRef_->createHandle(entityID));
    } else if(!satisfies(entityID) && find != entities_.end()) {
        entities_.erase(find);
    }
}

bool ent::BaseSystem::satisfies(ent::EntityID entityID) {
    return (filter_ & managerRef_->getMask(entityID)) == filter_;
}

std::vector<ent::Handle>::iterator ent::BaseSystem::findEntity(ent::EntityID entityID) {
    return std::find_if(entities_.begin(), entities_.end(), [&](ent::Handle& handle) {
        return handle.id() == entityID;
    });
}
