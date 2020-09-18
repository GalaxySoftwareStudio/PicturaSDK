function sleep(a)
    local sec = tonumber(os.clock() + a);
    while (os.clock() < sec) do end
end

workspace "PicturaSDK"
    architecture "x86_64"

    startproject "PicturaDemo"
    configurations {"Debug", "Release"}
    flags {"MultiProcessorCompile"}

    if (os.target() == "windows") then outputDirName = "Windows" end
    if (os.target() == "macosx") then outputDirName = "MacOS" end
    if (os.target() == "unix") then outputDirName = "Unix" end
    if (os.target() == "linux") then outputDirName = "Linux" end
    if (os.target() == "bsd") then outputDirName = "BSD" end

    print("Generating Pictura SDK project files...")

    print("Creating framework output directory...")
    os.mkdir("./Framework")
    print("Creating intermediate directory...")
    os.mkdir("./Intermediate")

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

    -- Pictura SDK project --
    project "PicturaFramework"
        location "Sources"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        targetname("Pictura-%{cfg.buildcfg}")
        print("Target system : " .. outputDirName);
        targetdir("Framework/" .. outputDirName .. "/")
        objdir("Intermediate/%{prj.name}/" .. outputDirName .. "/")
        libdirs {"Libraries/**"}

        pchheader "PicturaPCH.h"
        pchsource "Sources/PicturaPCH.cpp"

        files {"./Sources/**.h", "./Sources/**.cpp"}

        defines {"_CRT_SECURE_NO_WARNINGS"}

        includedirs {"./Sources", "./Libraries"}

        functionlevellinking "on"
        
        filter "system:windows"
            system "Windows"
            platforms {"Win64"}
            linkoptions {"/ignore:4006"}
        
        filter "system:linux"
        system "Linux"
        platforms {"Linux"}
        links {"pthread"}
        buildoptions {"-pthread", "-lpthread"}
        
        filter "system:macosx"
        system "macosx"
        platforms {"MacOS"}
            links {"pthread"}
            buildoptions {"-pthread", "-lpthread"}

        filter "configurations:Debug"
            defines "PICTURA_DEBUG"
            links {"vulkan-1"}
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "PICTURA_RELEASE"
            links {"vulkan-1"}
            runtime "Release"
            optimize "on"

    -- Pictura Demo project --
    project "PicturaDemo"
        location "Examples/%{prj.name}/Sources"
        kind "WindowedApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        targetname("%{prj.name}-%{cfg.buildcfg}")
        targetdir("Examples/%{prj.name}/Build/" .. outputDirName .. "/")
        objdir("Examples/%{prj.name}/Intermediate/" .. outputDirName .. "/")

        files {
            "./Examples/%{prj.name}/Sources/**.h",
            "./Examples/%{prj.name}/Sources/**.cpp"
        }

        includedirs {"./Sources", "./Libraries"}

        links {"PicturaFramework"}

        postbuildcommands {
            "{ECHO} Copying application ressources...",
            "{MKDIR} %{prj.location}../Build/" .. outputDirName .. "/Ressources",
            "{MKDIR} %{prj.location}../Build/" .. outputDirName .. "/Ressources/Shaders",
            "{COPY} %{prj.location}/../Ressources/Shaders/ %{prj.location}/../Builds/" .. outputDirName.. "/Ressources/Shaders/",
            "{ECHO} Application ressources copied !"
        }

        filter "system:windows"
            system "Windows"
            platforms {"Win64"}

        filter "system:linux"
            system "Linux"
            platforms {"Linux"}
            links {"pthread"}

        filter "system:macosx"
            system "macosx"
            platforms {"MacOS"}
            links {"pthread"}

        filter "configurations:Debug"
            defines "APPLICATION_DEBUG"
            runtime "Debug"
            symbols "on"
            optimize "off"

        filter "configurations:Release"
            defines "APPLICATION_RELEASE"
            runtime "Release"
            optimize "speed"

-- Completion delay
sleep(1)