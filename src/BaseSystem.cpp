#include "../include/BaseSystem.h"

#include "../include/Manager.h"
#include "../include/Handle.h"

void ent::BaseSystem::entityAdded(ent::EntityID entityID) {
    if(satisfies(entityID)) {
        entities.push_back(managerRef->createHandle(entityID));
    }
}

void ent::BaseSystem::entityRemoved(ent::EntityID entityID) {
    if(satisfies(entityID)) {
        entities.erase(findEntity(entityID));
    }
}

void ent::BaseSystem::entityModified(ent::EntityID entityID) {
    auto find = findEntity(entityID);
    if(satisfies(entityID) && find == entities.end()) {
        entities.push_back(managerRef->createHandle(entityID));
    } else if(!satisfies(entityID) && find != entities.end()) {
        entities.erase(find);
    }
}

bool ent::BaseSystem::satisfies(ent::EntityID entityID) {
    return (filter & managerRef->getMask(entityID)) == filter;
}

std::vector<ent::Handle>::iterator ent::BaseSystem::findEntity(ent::EntityID entityID) {
    return std::find_if(entities.begin(), entities.end(), [&](ent::Handle& handle) {
        return handle.id() == entityID;
    });
}
