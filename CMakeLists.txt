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
target_include_directories(Lsdl2 PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/SDL2/include)
target_link_libraries(Lsdl2 SDL2main SDL2-static)
