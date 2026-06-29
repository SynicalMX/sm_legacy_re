#include "../include/memory.h"

namespace SM {
    SM_API uintptr_t Memory::Base() {
        static auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
        return base;
    }
}
