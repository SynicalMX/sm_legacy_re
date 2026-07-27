#pragma once
#include <cstdint>

namespace SM::Offsets {
	inline constexpr uintptr_t ContraptionStart = 0x2D6270;
	inline constexpr uintptr_t DevMode = 0x1267497;
	inline constexpr uintptr_t Logger = 0x27B150;
}

namespace SM::Functions {
	typedef int64_t (*PFN_ContraptionStart)(int64_t arg_1, int32_t arg_2, char16_t** arg_3);
}
