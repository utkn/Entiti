#ifndef ENTITI_ENTITYHANDLE_H
#define ENTITI_ENTITYHANDLE_H

#include "Manager.h"

namespace ent {
    class Handle {
    public:
        Handle(Manager* manager, EntityID id) : m_manager(manager), m_id(id) {}
        template <typename T, typename... Args>
        void add(Args&&... args) {
            m_manager->add_component<T>(m_id, std::forward<Args>(args)...);
        }

        template <typename T>
        T& get() {
            return m_manager->get_component<T>(m_id);
        }

        template <typename T>
        void remove() {
            m_manager->remove_component<T>(m_id);
        }

        template <typename T>
        bool has() {
            return m_manager->get_mask(m_id)[m_manager->get_comp_id<T>()];
        }

        void destroy();
        EntityID get_id();
    private:
        Manager* m_manager;
        EntityID m_id;
    };

}

#endif //ENTITI_ENTITYHANDLE_H
