#include "../include/BaseSystem.h"

#include "../include/Manager.h"
#include "../include/Handle.h"

void ent::BaseSystem::entityAdded(ent::EntityID entityID) {
    if(satisfies(entityID)) {
        m_entities.push_back(m_managerRef->createHandle(entityID));
    }
}

void ent::BaseSystem::entityRemoved(ent::EntityID entityID) {
    if(satisfies(entityID)) {
        m_entities.erase(findEntity(entityID));
    }
}

void ent::BaseSystem::entityModified(ent::EntityID entityID) {
    auto find = findEntity(entityID);
    if(satisfies(entityID) && find == m_entities.end()) {
        m_entities.push_back(m_managerRef->createHandle(entityID));
    } else if(!satisfies(entityID) && find != m_entities.end()) {
        m_entities.erase(find);
    }
}

bool ent::BaseSystem::satisfies(ent::EntityID entityID) {
    return (m_filter & m_managerRef->getMask(entityID)) == m_filter;
}

std::vector<ent::Handle>::iterator ent::BaseSystem::findEntity(ent::EntityID entityID) {
    return std::find_if(m_entities.begin(), m_entities.end(), [&](ent::Handle& handle) {
        return handle.getID() == entityID;
    });
}
