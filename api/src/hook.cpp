#include "../include/hook.h"
#include <stdexcept>
#include <MinHook.h>

namespace SM {

    static int s_refCount = 0;

    Hook::Hook(void* target, void* detour, void** original)
        : m_target(target), m_detour(detour), m_original(original), m_enabled(false)
    {
        if (s_refCount == 0)
        {
            if (MH_Initialize() != MH_OK)
                throw std::runtime_error("MH_Initialize failed");
        }
        ++s_refCount;

        if (MH_CreateHook(m_target, m_detour, m_original) != MH_OK)
            throw std::runtime_error("MH_CreateHook failed");
    }

    Hook::~Hook()
    {
        Disable();
        MH_RemoveHook(m_target);

        --s_refCount;
        if (s_refCount == 0)
            MH_Uninitialize();
    }

    bool Hook::Enable()
    {
        if (m_enabled) return true;
        m_enabled = MH_EnableHook(m_target) == MH_OK;
        return m_enabled;
    }

    bool Hook::Disable()
    {
        if (!m_enabled) return true;
        bool ok = MH_DisableHook(m_target) == MH_OK;
        if (ok) m_enabled = false;
        return ok;
    }

}