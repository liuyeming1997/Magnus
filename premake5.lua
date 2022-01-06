workspace "Magnus"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "Magnus/vendor/GLFW/include"
IncludeDir["Glad"] = "Magnus/vendor/Glad/include"
IncludeDir["ImGui"] = "Magnus/vendor/imgui"

group "Dependencies"
	include "Magnus/vendor/GLFW"
	include "Magnus/vendor/Glad"
	include "Magnus/vendor/imgui"
group ""

project "Magnus"
	location "Magnus"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mgpch.h"
	pchsource "Magnus/src/mgpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGUi",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS",
			"MG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MG_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Magnus/vendor/spdlog/include",
		"Magnus/src"
	}

	links
	{
		"Magnus"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MG_DIST"
		runtime "Release"
		optimize "On"