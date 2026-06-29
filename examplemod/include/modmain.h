#pragma once
#include "../../api/include/imod.h"
#include "modmeta.h"

class ExampleMod : public SM::IMod {
    public:
    ExampleMod() : IMod({ MOD_NAME, MOD_PACKAGE, MOD_VERSION, MOD_AUTHOR }) {}

    void OnInit() override;
    void OnUpdate() override;
    void OnDestroy() override;
};
