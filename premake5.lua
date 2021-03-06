workspace "SpaceInvaders"
	startproject "SpaceInvaders"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (for entire solution)
IncludeDir = {}
IncludeDir["GLFW"] = "SpaceInvaders/vendor/GLFW/include"
IncludeDir["glad"] = "SpaceInvaders/vendor/glad/include"
IncludeDir["glm"] = "SpaceInvaders/vendor/glm"

include "SpaceInvaders/vendor/GLFW"
include "SpaceInvaders/vendor/glad"

project "SpaceInvaders"
	location "SpaceInvaders"
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
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir}.glm"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEV_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "DEV_RELEASE"
		optimize "On"

