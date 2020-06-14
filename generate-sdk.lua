workspace "PicturaSDK"
	architecture "x86_64"

	configurations {"Debug", "Release"}

	flags {"MultiProcessorCompile"}

if (os.target() == "windows") then outputDirName = "Windows" end
if (os.target() == "macosx") then outputDirName = "MacOS" end
if (os.target() == "unix") then outputDirName = "Linux" end
if (os.target() == "bsd") then outputDirName = "BSD" end

print("Generating Pictura SDK project files...")

filter "system:windows"
	system "Windows"
	platforms {"Win64"}

filter "system:linux"
	system "Linux"
	platforms {"Linux"}

filter "system:macosx"
	system "macosx"
	platforms {"MacOS"}

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

project "PicturaFramework"
	location "Sources"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetname ("Pictura-%{cfg.buildcfg}")
	print("Target system : " .. outputDirName);
	targetdir ("Framework/" .. outputDirName .. "/")
	objdir ("Intermediate/" .. outputDirName .. "/")

	print("Creating framework output directory...")
	os.mkdir("./Framework")
	print("Creating intermediate directory...")
	os.mkdir("./Intermediate")

	pchheader "PicturaPCH.h"
	pchsource "Sources/PicturaPCH.cpp"

	files
	{
		"./Sources/**.h",
		"./Sources/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"./Sources"
	}

	filter "system:windows"
		system "Windows"
		platforms {"Win64"}


	filter "system:linux"
		system "Linux"
		platforms {"Linux"}
		
	filter "system:macosx"
		system "macosx"
		platforms {"MacOS"}

	filter "configurations:Debug"
		defines "PICTURA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PICTURA_RELEASE"
		runtime "Release"
		optimize "on"