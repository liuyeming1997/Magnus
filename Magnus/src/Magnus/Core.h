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

#define BIT(x) 1<<x