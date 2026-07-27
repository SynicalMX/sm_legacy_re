#pragma once
#include "../../../api/include/hook.h"
#include "../../../api/include/offsets.h"
#include <cstdint>
using namespace SM::Functions;

class ContraptionStartHook : public SM::Hook {
public:
	ContraptionStartHook();
	~ContraptionStartHook() = default;

	static int64_t Detour(int64_t arg_1, int32_t arg_2, char16_t** arg_3);
	static PFN_ContraptionStart Original;
};
