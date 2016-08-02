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
        void attach(BaseSystem& system);
        void notifyEntityRemoved(EntityID id);
        void notifyEntityModified(EntityID id);
        void update(double dt);

        template <typename T, typename... Args>
        void add(EntityID entityID, Args&&... args) {
            EntityID compID = CompIDGenerator::get<T>();
            entityCompMap[entityID][compID].reset(new T(std::forward<Args>(args)...));
            entityMaskMap[entityID][compID] = true;
            notifyEntityModified(entityID);
        }

        template <typename T>
        void remove(EntityID entityID) {
            EntityID compID = CompIDGenerator::get<T>();
            entityCompMap[entityID][compID].reset(nullptr);
            entityMaskMap[entityID][compID] = false;
            notifyEntityModified(entityID);
        }

        template <typename T>
        T& get(EntityID entityID) {
            return *static_cast<T*>(entityCompMap[entityID][CompIDGenerator::get<T>()].get());
        }
    private:
        EntityID nextID = 0;
        EntityCompMap entityCompMap;
        EntityMaskMap entityMaskMap;
        std::vector<EntityID> entities;
        std::vector<BaseSystem*> systems;
    };
}


#endif //ENTITI_MANAGER_H