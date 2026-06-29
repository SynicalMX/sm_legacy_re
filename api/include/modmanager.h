#pragma once
#include <vector>
#include "imod.h"

namespace SM {
	class SM_API ModManager {
	public:
		ModManager() = delete;

		static void Register(IMod* mod);
		static void Init();
		static void Update();
		static void Destroy();

		static const std::vector<IMod*>& GetMods();
	};
}
