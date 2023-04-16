cmake_minimum_required(VERSION 3.20)

project(QuickLab)

# Add exe project
function(addProject proj)
    file(GLOB projAll ./src/${proj}/*)
    add_executable(${proj} ${projAll})
endfunction(addProject proj)

addproject(Ltemplate)
addproject(TwinTaskKill)
addproject(TqueryWindowsGraphicDriver)
target_link_libraries(TqueryWindowsGraphicDriver ole32)

# Add OpenCV library
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

addproject(LprojectionPlane)
target_link_libraries(LprojectionPlane ${OpenCV_LIBS})

# Add GoogleTest library
add_subdirectory(3rd_party/googletest)
# Add GoogleBenchmark library
add_subdirectory(3rd_party/benchmark)
include_directories(benchmark/include)

addproject(Lopencv)
target_link_libraries(Lopencv ${OpenCV_LIBS})
target_link_libraries(Lopencv benchmark::benchmark)

# Add zlib library
add_subdirectory(3rd_party/zlib)
include_directories(3rd_party/zlib)
# Add file for zlib library to build, otherwise it will not build
include_directories(${CMAKE_CURRENT_BINARY_DIR}/3rd_party/zlib)

addproject(Lzlib)
target_link_libraries(Lzlib zlibstatic)

# Add sdl2 library
set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
add_subdirectory(3rd_party/SDL2)

addproject(Lsdl2)
target_include_directories(
    Lsdl2 PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/SDL2/include)
target_link_libraries(Lsdl2 SDL2main SDL2-static)

# Add eigen3 library Use vcpkg to install eigen3
set(Eigen3_DIR $ENV{VCPKG_DIR}/installed/x64-windows/share/eigen3)
find_package(Eigen3 CONFIG REQUIRED)
addproject(LEigen3)
target_link_libraries(LEigen3 Eigen3::Eigen)

# Add glfw3 library Use vcpkg to install glfw3
set(glfw3_DIR $ENV{VCPKG_DIR}/installed/x64-windows/share/glfw3)
find_package(glfw3 CONFIG REQUIRED)
# Add imgui library Use vcpkg to install imgui
set(imgui_DIR $ENV{VCPKG_DIR}/installed/x64-windows/share/imgui)
find_package(imgui CONFIG REQUIRED)
# Add sfml library Use vcpkg to install sfml
set(SFML_DIR $ENV{VCPKG_DIR}/installed/x64-windows/share/SFML)
find_package(SFML CONFIG REQUIRED COMPONENTS graphics system window)
# Add ImGui-SFML library Use vcpkg to install ImGui-SFML
set(ImGui-SFML_DIR $ENV{VCPKG_DIR}/installed/x64-windows/share/ImGui-SFML)
find_package(ImGui-SFML CONFIG REQUIRED)

addproject(Limgui)
target_include_directories(Limgui PUBLIC ${imgui_INCLUDE_DIRS})
target_link_libraries(Limgui PRIVATE imgui::imgui sfml-graphics sfml-system
                                     sfml-window ImGui-SFML::ImGui-SFML glfw)
