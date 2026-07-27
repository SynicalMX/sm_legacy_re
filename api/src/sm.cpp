#include "../include/sm.h"
#include "../include/memory.h"
#include "../include/offsets.h"

namespace SM {
    bool SM_API IsDevMode() {
        return Memory::Read<bool>(Offsets::DevMode);
    }
}
