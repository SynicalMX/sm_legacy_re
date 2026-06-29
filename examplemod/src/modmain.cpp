#include "../include/modmain.h"
#include <iostream>

void ExampleMod::OnInit() {
    std::cout << "Hello, from example mod!" << std::endl;
}

void ExampleMod::OnUpdate() {
    std::cout << "Dev Mode: " << SM::IsDevMode() << std::endl;
}

void ExampleMod::OnDestroy() {
}

extern "C" __declspec(dllexport) SM::IMod* CreateMod() {
    return new ExampleMod();
}
