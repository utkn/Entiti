#ifndef ENTITI_ENTITYHANDLE_H
#define ENTITI_ENTITYHANDLE_H

#include "Manager.h"

namespace ent {
    class Handle {
    public:
        Handle(Manager* manager, EntityID id) : managerRef(manager), id(id) {}
        template <typename T, typename... Args>
        void add(Args&&... args) {
            managerRef->add<T>(id, std::forward<Args>(args)...);
        }

        template <typename T>
        T& get() {
            return managerRef->get<T>(id);
        }

        template <typename T>
        void remove() {
            managerRef->remove<T>(id);
        }

        template <typename T>
        bool has() {
            return managerRef->getMask(id)[CompIDGenerator::get<T>()];
        }

        void destroy();
        EntityID getID();
    private:
        Manager* managerRef;
        EntityID id;
    };

}

#endif //ENTITI_ENTITYHANDLE_H
