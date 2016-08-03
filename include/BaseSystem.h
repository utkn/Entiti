#ifndef ENTITI_BASESYSTEM_H
#define ENTITI_BASESYSTEM_H

#include <vector>
#include "Misc.h"

namespace ent {
    class Handle;
    class Manager;

    class BaseSystem {
    protected:
        void entityAdded(EntityID entityID);
        void entityRemoved(EntityID entityID);
        void entityModified(EntityID entityID);
        bool satisfies(EntityID entityID);
        std::vector<Handle>::iterator findEntity(EntityID entityID);
    public:
        virtual void update(double dt) = 0;
    protected:
        friend class Manager;
        Mask m_filter;
        std::vector<Handle> m_entities;
        Manager* m_managerRef;
    };
}


#endif //ENTITI_BASESYSTEM_H
