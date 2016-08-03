#ifndef ENTITI_ENTITYHANDLE_H
#define ENTITI_ENTITYHANDLE_H

#include "Manager.h"

namespace ent {
    class Handle {
    public:
        Handle(Manager* manager, EntityID id) : m_managerRef(manager), m_id(id) {}
        template <typename T, typename... Args>
        void add(Args&&... args) {
            m_managerRef->addComponent<T>(m_id, std::forward<Args>(args)...);
        }

        template <typename T>
        T& get() {
            return m_managerRef->getComponent<T>(m_id);
        }

        template <typename T>
        void remove() {
            m_managerRef->removeComponent<T>(m_id);
        }

        template <typename T>
        bool has() {
            return m_managerRef->getMask(m_id)[m_managerRef->getCompId<T>()];
        }

        void destroy();
        EntityID getID();
    private:
        Manager* m_managerRef;
        EntityID m_id;
    };

}

#endif //ENTITI_ENTITYHANDLE_H
