#pragma once
#include "../../api/include/imod.h"
#include "modmeta.h"

class ResearchMod : public SM::IMod {
    public:
    ResearchMod() : IMod({ MOD_NAME, MOD_PACKAGE, MOD_VERSION, MOD_AUTHOR }) {}

    void OnInit() override;
    void OnUpdate() override;
    void OnDestroy() override;
};
