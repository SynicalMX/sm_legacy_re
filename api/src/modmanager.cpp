#include "../include/modmanager.h"
#include <vector>

namespace SM {

	static std::vector<IMod*> s_mods;

	void ModManager::Register(IMod* mod)
	{
		s_mods.push_back(mod);
	}

	void ModManager::Init()
	{
		for (IMod* mod : s_mods)
			mod->OnInit();
	}

	void ModManager::Update()
	{
		for (IMod* mod : s_mods)
			mod->OnUpdate();
	}

	void ModManager::Destroy()
	{
		for (IMod* mod : s_mods)
		{
			mod->OnDestroy();
			delete mod;
		}
		s_mods.clear();
	}

	const std::vector<IMod*>& ModManager::GetMods()
	{
		return s_mods;
	}

}
