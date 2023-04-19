cmake_minimum_required(VERSION 3.20)

project(QuickLab)

# Add exe project
function(addProject proj)
    file(GLOB projAll ./${proj}/*)
    add_executable(${proj} ${projAll})
endfunction(addProject proj)

# Add OpenCV library
find_package(OpenCV REQUIRED)

# Add GoogleTest and GoogleBenchmark library with vcpkg
find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

# Add zlib library with vcpkg
find_package(ZLIB REQUIRED)

# Add sdl2 library with vcpkg
find_package(SDL2 CONFIG REQUIRED)

# Add eigen3 library with vcpkg
find_package(Eigen3 CONFIG REQUIRED)

# Add glfw3, imgui, sfml and ImGui-SFML library with vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML CONFIG REQUIRED COMPONENTS graphics system window)
find_package(ImGui-SFML CONFIG REQUIRED)

add_subdirectory(src)
