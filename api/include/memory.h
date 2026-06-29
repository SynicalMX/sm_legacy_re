#pragma once
#include "sm.h"

namespace SM {
    namespace Memory {

        SM_API uintptr_t Base();

        template<typename T> static T Read(uintptr_t offset) {
            return *reinterpret_cast<T*>(Base() + offset);
        }

        template<typename T> static void Write(uintptr_t offset, const T& value) {
            *reinterpret_cast<T*>(Base() + offset) = value;
        }

        template<typename T> static T* Ptr(uintptr_t offset) {
            return reinterpret_cast<T*>(Base() + offset);
        }
    };
}
