cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(TARGET out)
set(CXX_STANDARD 17)

set(LIBRARIES GL GLEW glfw freetype spdlog assimp)
file(GLOB SOURCES "Engine/*/*.cpp" "Engine/*/*/*.cpp" "Engine/*/*.h" "Engine/*/*/*.h" main.cpp gui.h)
file(GLOB INCLUDE_DIR "Engine/*/"  ${CMAKE_SOURCE_DIR}/Engine)
file(GLOB LIBS_INCLUDE_DIRECTORY "Engine/Vendor/*")

find_package(spdlog REQUIRED)


#add_subdirectory(Engine/Vendor/box2d/src)
add_executable(${TARGET} ${SOURCES})
set_target_properties(${TARGET} PROPERTIES CXX_STANDARD ${CXX_STANDARD})
target_link_libraries(${TARGET} ${LIBRARIES} spdlog::spdlog) #box2d)
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIR})

