#pragma once
#ifdef MG_PLATFORM_WINDOWS
	#ifdef MG_BUILD_DLL
		#define MAGNUS_API __declspec(dllexport)
	#else
		#define MAGNUS_API __declspec(dllimport)
	#endif // MG_BUILD_DLL
#else
	#error Magnus only supports Windows!

#endif // MG_PLATFORM_WINDOWS

#define MG_ASSERT(x, ...) {if(!x){MG_ERROR("ASSERT ERROR: {0}", __VA_ARGS__); __debugbreak();}}
#define MG_CORE_ASSERT(x, ...) {if(!x){MG_CORE_ERROR("ASSERT CORE ERROR: {0}", __VA_ARGS__); __debugbreak();}}
#define BIT(x) 1<<x