workspace "raytracing"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "raytracing"

include "kettle/kettleCore"

project "raytracing"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("obj/%{cfg.buildcfg}")

	links { "kettle" }

    includedirs {
        "src",

        "kettle/kettle/src",
		"kettle/thirdparty/glad/include",
        "kettle/thirdparty/imgui"
    }

    files {
        "src/**.h",
        "src/**.cpp",
    }

    filter "Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"
        links { "pthread", "dl" }
		links { "glfw", "glad", "imgui" }
