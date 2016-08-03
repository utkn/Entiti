#include "../include/Handle.h"

void ent::Handle::destroy() {
    m_managerRef->removeEntity(m_id);
    m_managerRef = nullptr;
}

ent::EntityID ent::Handle::getID() {
    return m_id;
}