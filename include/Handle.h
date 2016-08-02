#ifndef ENTITI_ENTITYHANDLE_H
#define ENTITI_ENTITYHANDLE_H

#include "Manager.h"

namespace ent {
    class Handle {
    private:
        Manager* managerRef_;
        EntityID id_;
    public:
        Handle(Manager* manager, EntityID id) : managerRef_(manager), id_(id) {}
        template <typename T, typename... Args>
        void add(Args&&... args) {
            managerRef_->add<T>(id_, std::forward<Args>(args)...);
        }

        template <typename T>
        T& get() {
            return managerRef_->get<T>(id_);
        }

        template <typename T>
        void remove() {
            managerRef_->remove<T>(id_);
        }

        template <typename T>
        bool has() {
            return managerRef_->getMask(id_)[CompIDGenerator::get<T>()];
        }

        void destroy();
        EntityID id();
    };
}

#endif //ENTITI_ENTITYHANDLE_H
