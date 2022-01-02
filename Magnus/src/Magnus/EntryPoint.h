#pragma once
#ifdef MG_PLATFORM_WINDOWS
#include "Application.h"

extern Magnus::Application* Magnus::CreateApplication();
int main(int argc, char** argv) {
	printf("haha");
	auto app = Magnus::CreateApplication();
	app->Run();
	delete app;
}
#endif // MG_PLATFORM_WINDOWS
