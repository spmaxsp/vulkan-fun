cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME VULKAN-FUN)

project(${PROJECT_NAME})

#################### OUTPUT DIRECTORY ####################

### set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#################### SOURCE FILES ####################

### set source files
set(SOURCE_FILES 
    src/main.cpp                            ### main file
    src/vulkan_base/vulkan_device.cpp
)

####################  EXECUTABLE  ####################

### add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


#################### LIBRARIES ####################

### include spdlog
add_subdirectory(libs/spdlog)
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} spdlog)

### include imgui
set(IMGUI_FILES libs/imgui/imgui.cpp libs/imgui/imgui_demo.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_tables.cpp libs/imgui/imgui_widgets.cpp libs/imgui/backends/imgui_impl_sdl2.cpp libs/imgui/backends/imgui_impl_vulkan.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE libs/imgui libs/imgui/backends)

### include SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

### include Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})