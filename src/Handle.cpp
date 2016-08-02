#include "../include/Handle.h"

void ent::Handle::destroy() {
    managerRef->removeEntity(id);
    managerRef = nullptr;
}

ent::EntityID ent::Handle::getID() {
    return id;
}