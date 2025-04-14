cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(VulkanTutorial)

add_executable(VulkanTutorial)
target_sources(VulkanTutorial PRIVATE 
    src/main.cpp 
    src/triangle.cpp
    src/device.cpp
    src/window.cpp
    )

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(VulkanTutorial PRIVATE
Vulkan::Vulkan
glfw
)