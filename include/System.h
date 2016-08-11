#ifndef ENTITI_SYSTEM_H
#define ENTITI_SYSTEM_H

#include <iostream>
#include "BaseSystem.h"
#include "Manager.h"

namespace ent {
    template<typename... Deps>
    class System : public BaseSystem {
    public:
        void createFilter() override {
            if(m_manager == nullptr) {
                std::cerr << "Can not create filter mask for an unassigned system.";
                exit(1);
            }
            expand((m_filter[m_manager->get_comp_id<Deps>()] = true)...);
        }
    };
}

#endif //ENTITI_SYSTEM_H
