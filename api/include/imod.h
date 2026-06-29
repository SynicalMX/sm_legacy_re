#pragma once
#include "sm.h"
#include <string>

namespace SM {

    struct SM_API ModMeta {
        std::string name;
        std::string package;
        std::string version;
        std::string author;
    };

    class SM_API IMod {
    public:
        explicit IMod(ModMeta meta) : m_meta(std::move(meta)) {}
        virtual ~IMod() = default;

        const ModMeta& GetModMeta() const { return m_meta; }

        virtual void OnInit()    = 0;
        virtual void OnUpdate()  = 0;
        virtual void OnDestroy() = 0;

    private:
        ModMeta m_meta;
    };

}