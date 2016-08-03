#ifndef ENTITI_SYSTEM_H
#define ENTITI_SYSTEM_H

#include <iostream>
#include "BaseSystem.h"
#include "Manager.h"

namespace ent {
    template<typename... Deps>
    class System : public BaseSystem {
    protected:
        void createFilter() {
            if(m_managerRef == nullptr) {
                std::cerr << "Can not create filter mask for an unassigned system.";
                exit(1);
            }
            expand((m_filter[m_managerRef->getCompId<Deps>()] = true)...);
        }
    };
}

#endif //ENTITI_SYSTEM_H
