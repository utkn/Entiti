#ifndef ENTITI_MISC_H
#define ENTITI_MISC_H

#include <unordered_map>
#include <array>
#include <bitset>
#include "Component.h"

namespace ent {
    constexpr int MAX_COMPONENTS = 256;
    typedef unsigned CompID;
    typedef unsigned EntityID;
    typedef std::array<std::unique_ptr<Component>, MAX_COMPONENTS> ComponentArray;
    typedef std::unordered_map<EntityID, ComponentArray> EntityCompMap;
    typedef std::bitset<MAX_COMPONENTS> Mask;
    typedef std::unordered_map<EntityID, Mask> EntityMaskMap;

    struct CompIDGenerator {
    public:
        template <typename T>
        static CompID get() {
            static CompID id = next++;
            return id;
        }
    private:
        static CompID next;
    };

    template <typename... Args>
    void expand(Args&&... args) {}
}

#endif //ENTITI_MISC_H
