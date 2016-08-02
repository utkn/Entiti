#ifndef ENTITI_SYSTEM_H
#define ENTITI_SYSTEM_H

#include "BaseSystem.h"

namespace ent {
    template<typename... Deps>
    class System : public BaseSystem {
    protected:
        System() {
            expand((filter_[CompIDGenerator::get<Deps>()] = true)...);
        }
    };
}

#endif //ENTITI_SYSTEM_H
