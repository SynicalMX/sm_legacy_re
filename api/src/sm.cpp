#include "../include/sm.h"
#include "../include/memory.h"

namespace SM {
    bool SM_API IsDevMode() {
        return Memory::Read<bool>(0x1267497);
    }
}
