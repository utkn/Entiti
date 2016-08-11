#ifndef ENTITI_BASESYSTEM_H
#define ENTITI_BASESYSTEM_H

#include <vector>
#include "Misc.h"

namespace ent {
    class Manager;
    class Handle;

    class BaseSystem {
    protected:
        void entity_added(EntityID entity_id);
        void entity_removed(EntityID entity_id);
        void entity_modified(EntityID entity_id);
        bool satisfies(EntityID entity_id);
        std::vector<EntityID>::iterator find_entity(EntityID entity_id);
        virtual void createFilter() = 0;
    public:
        virtual void update(double dt) = 0;
    protected:
        friend class Manager;
        Mask m_filter;
        std::vector<EntityID> m_entities;
        Manager* m_manager;
    };
}


#endif //ENTITI_BASESYSTEM_H
