#ifndef ENTITI_MANAGER_H
#define ENTITI_MANAGER_H

#include <vector>
#include "Misc.h"
#include "BaseSystem.h"

namespace ent {
    class Handle;

    class Manager {
    public:
        Handle newEntity();
        Handle createHandle(EntityID entityID);
        void removeEntity(EntityID entityID);
        Mask& getMask(EntityID entityID);
        void attachSystem(BaseSystem &system);
        void notifyEntityRemoved(EntityID id);
        void notifyEntityModified(EntityID id);
        void update(double dt);

        template <typename T, typename... Args>
        void addComponent(EntityID entityID, Args &&... args) {
            EntityID compID = getCompId<T>();
            m_entityCompMap[entityID][compID].reset(new T(std::forward<Args>(args)...));
            m_entityMaskMap[entityID][compID] = true;
            notifyEntityModified(entityID);
        }

        template <typename T>
        void removeComponent(EntityID entityID) {
            EntityID compID = getCompId<T>();
            m_entityCompMap[entityID][compID].reset(nullptr);
            m_entityMaskMap[entityID][compID] = false;
            notifyEntityModified(entityID);
        }

        template <typename T>
        T& getComponent(EntityID entityID) {
            return *static_cast<T*>(m_entityCompMap[entityID][getCompId<T>()].get());
        }

        template <typename T>
        CompID getCompId() {
            static CompID id = ++m_nextCompID;
            return id;
        }

    private:
        EntityID m_nextEntityID = 0;
        CompID m_nextCompID = 0;

        EntityCompMap m_entityCompMap;
        EntityMaskMap m_entityMaskMap;
        std::vector<EntityID> m_entities;
        std::vector<std::unique_ptr<BaseSystem>> m_systems;
    };
}


#endif //ENTITI_MANAGER_H