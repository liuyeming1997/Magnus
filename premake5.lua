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
IncludeDir["glm"] = "Magnus/vendor/glm"
IncludeDir["stb_image"] = "Magnus/vendor/stb_image"
group "Dependencies"
	include "Magnus/vendor/GLFW"
	include "Magnus/vendor/Glad"
	include "Magnus/vendor/imgui"
group ""

project "Magnus"
	location "Magnus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mgpch.h"
	pchsource "Magnus/src/mgpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",
		"%{prj.name}/vendor/stb_image/stb_image.h"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}


	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}"

	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGUi",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS",
			"MG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		
	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MG_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Magnus/src",
		"Magnus/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Magnus"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MG_DIST"
		runtime "Release"
		optimize "on"