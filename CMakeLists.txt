cmake_minimum_required(VERSION 3.11.0)

set(PROJECT_NAME "Percolation-Demo")
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
# set(CMAKE_TOOLCHAIN_FILE "D:\\Program Files\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
message("CMAKE_MOD: ${CMAKE_MODULE_PATH}")
message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")


set(SOURCE_FILES
"src/main.cpp"
"src/grid.cpp"
)

set(HEADER_FILES
"src/grid.hpp"
"src/logging.hpp"
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "src/include")

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)