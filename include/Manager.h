#ifndef ENTITI_MANAGER_H
#define ENTITI_MANAGER_H

#include <vector>
#include "Misc.h"
#include "BaseSystem.h"

namespace ent {
    class Handle;

    class Manager {
    public:
        Handle new_entity();
        Handle create_handle(EntityID entityID);
        void remove_entity(EntityID entityID);
        Mask& get_mask(EntityID entityID);
        void attach_system(BaseSystem &system);
        void notify_entity_removed(EntityID id);
        void notify_entity_modified(EntityID id);
        void update(double dt);

        template <typename T, typename... Args>
        void add_component(EntityID entityID, Args &&... args) {
            EntityID compID = get_comp_id<T>();
            m_entity_comp_map[entityID][compID].reset(new T(std::forward<Args>(args)...));
            m_entity_mask_map[entityID][compID] = true;
            notify_entity_modified(entityID);
        }

        template <typename T>
        void remove_component(EntityID entityID) {
            EntityID compID = get_comp_id<T>();
            m_entity_comp_map[entityID][compID].reset(nullptr);
            m_entity_mask_map[entityID][compID] = false;
            notify_entity_modified(entityID);
        }

        template <typename T>
        T& get_component(EntityID entityID) {
            return *static_cast<T*>(m_entity_comp_map[entityID][get_comp_id<T>()].get());
        }

        template <typename T>
        CompID get_comp_id() {
            static CompID id = ++m_next_comp_id;
            return id;
        }

    private:
        EntityID m_next_entity_id = 0;
        CompID m_next_comp_id = 0;

        EntityCompMap m_entity_comp_map;
        EntityMaskMap m_entity_mask_map;
        std::vector<EntityID> m_entities;
        std::vector<BaseSystem*> m_systems;
    };
}


#endif //ENTITI_MANAGER_H
