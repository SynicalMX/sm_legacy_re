#include "../../include/hooks/contraptionstart.h"
#include "../../../api/include/modmanager.h"
#include "../../../api/include/memory.h"
#include "../../include/loader.h"

PFN_ContraptionStart ContraptionStartHook::Original = nullptr;

ContraptionStartHook::ContraptionStartHook()
	: Hook(
		reinterpret_cast<void*>(SM::Memory::Base() + SM::Offsets::ContraptionStart),
		reinterpret_cast<void*>(Detour),
		reinterpret_cast<void**>(&Original)
	)
{}

int64_t ContraptionStartHook::Detour(int64_t arg_1, int32_t arg_2, char16_t** arg_3)
{
	auto result = Original(arg_1, arg_2, arg_3);

	static bool s_loaded = false;
	if (!s_loaded)
	{
		s_loaded = true;
		Loader::LoadMods();
		SM::ModManager::Init();
	}

	return result;
}
