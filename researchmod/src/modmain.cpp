#include "../include/modmain.h"
#include <iostream>

void ResearchMod::OnInit() {
    std::cout << "Hello, from example mod!" << std::endl;
}

void ResearchMod::OnUpdate() {
    std::cout << "Dev Mode: " << SM::IsDevMode() << std::endl;
}

void ResearchMod::OnDestroy() {
}

extern "C" __declspec(dllexport) SM::IMod* CreateMod() {
    return new ResearchMod();
}
