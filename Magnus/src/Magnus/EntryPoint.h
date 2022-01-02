#pragma once
#ifdef MG_PLATFORM_WINDOWS
#include "Application.h"

extern Magnus::Application* Magnus::CreateApplication();
int main(int argc, char** argv) {
	Magnus::Log::Init();
	MG_CLIENT_ERROR("error");
	MG_CLIENT_WARN("warn");
	MG_CORE_INFO("info");
	int a = 5;
	int b = 10;
	std::string c = "gou";
	MG_CORE_TRACE("trace {0} {1} {2}", a, b, c);
	auto app = Magnus::CreateApplication();
	app->Run();
	delete app;
}
#endif // MG_PLATFORM_WINDOWS
