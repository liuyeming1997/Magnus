workspace "Magnus"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Magnus"
	location "Magnus"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS",
			"MG_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MG_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MG_DIST"
		optimize "On"