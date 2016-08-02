#ifndef ENTITI_BASESYSTEM_H
#define ENTITI_BASESYSTEM_H

#include <vector>
#include "Misc.h"

namespace ent {
    class Handle;
    class Manager;

    class BaseSystem {
    protected:
        friend class Manager;
        Mask filter;
        std::vector<Handle> entities;
        Manager* managerRef;

        void entityAdded(EntityID entityID);
        void entityRemoved(EntityID entityID);
        void entityModified(EntityID entityID);
        bool satisfies(EntityID entityID);
        std::vector<Handle>::iterator findEntity(EntityID entityID);
    public:
        virtual void update(double dt) = 0;
    };
}


#endif //ENTITI_BASESYSTEM_H
