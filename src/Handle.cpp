#include "../include/Handle.h"

void ent::Handle::destroy() {
    managerRef_->removeEntity(id_);
    managerRef_ = nullptr;
}

ent::EntityID ent::Handle::id() {
    return id_;
}