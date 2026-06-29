#pragma once
#include "sm.h"

namespace SM {

    class SM_API Hook {
    public:
        Hook(void* target, void* detour, void** original);
        ~Hook();

        bool Enable();
        bool Disable();

        bool IsEnabled() const { return m_enabled; }

    private:
        void*  m_target;
        void*  m_detour;
        void** m_original;
        bool   m_enabled;
    };

}
