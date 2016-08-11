#include "Handle.h"

void ent::Handle::destroy() {
    m_manager->remove_entity(m_id);
    m_manager = nullptr;
}

ent::EntityID ent::Handle::get_id() {
    return m_id;
}
