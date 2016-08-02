#include <iostream>
#include "include/Entiti.h"

int main() {
    ent::Manager manager;
    ent::Handle handle = manager.newEntity();
    return 0;
}