#ifndef ENTITI_MANAGER_H
#define ENTITI_MANAGER_H

#include <vector>
#include "Misc.h"
#include "BaseSystem.h"

namespace ent {
    class Handle;

    class Manager {
        EntityID nextID_ = 0;
        EntityCompMap entityCompMap_;
        EntityMaskMap entityMaskMap_;
        std::vector<EntityID> entities_;
        std::vector<BaseSystem*> systems_;
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
            entityCompMap_[entityID][compID].reset(new T(std::forward<Args>(args)...));
            entityMaskMap_[entityID][compID] = true;
            notifyEntityModified(entityID);
        }

        template <typename T>
        void remove(EntityID entityID) {
            EntityID compID = CompIDGenerator::get<T>();
            entityCompMap_[entityID][compID].reset(nullptr);
            entityMaskMap_[entityID][compID] = false;
            notifyEntityModified(entityID);
        }

        template <typename T>
        T& get(EntityID entityID) {
            return *static_cast<T*>(entityCompMap_[entityID][CompIDGenerator::get<T>()].get());
        }
    };
}


#endif //ENTITI_MANAGER_H