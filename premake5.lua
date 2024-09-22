workspace "PaintApp-OpenGL"
    architecture "x64"
    startproject "PaintApp"

    configurations
    {
        "Debug",
        "Release"
    }

outputDir = "%{cfg.buildfg}-%{cfg.system}"

project "PaintApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    targetdir ("temp/bin/%{cfg.buildfg}")
    objdir ("temp/obj/%{cfg.buildfg}")

    files
    {
        "src/public/**.h",
        "src/private/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src/public/",
        "vendor/include",
        "vendor/include/gl",
        "vendor/include/glfw"
    }

    libdirs
    {
        "vendor/libs/gl",
        "vendor/libs/glfw"
    }

    links
    {
        "opengl32",
        "glfw3",
        "glew32"
    }