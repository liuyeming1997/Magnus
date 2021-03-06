#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace Magnus {
	class MAGNUS_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
	
}
//Core log macros
#define MG_CORE_ERROR(...) ::Magnus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MG_CORE_INFO(...) ::Magnus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MG_CORE_WARN(...) ::Magnus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MG_CORE_TRACE(...) ::Magnus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MG_CORE_FATAL(...)    ::Magnus::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define MG_ERROR(...) ::Magnus::Log::GetClientLogger()->error(__VA_ARGS__)
#define MG_INFO(...) ::Magnus::Log::GetClientLogger()->info(__VA_ARGS__)
#define MG_WARN(...) ::Magnus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MG_TRACE(...) ::Magnus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MG_FATAL(...)    ::Magnus::Log::GetCoreLogger()->critical(__VA_ARGS__)