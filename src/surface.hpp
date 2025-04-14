#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "window.hpp"
#include <vulkan/vulkan.h>

namespace vtt {
class Surface {
  VkSurfaceKHR surface;

public:
  void createSurface(Window &window, const VkInstance &instance);
  void destroySurface(const VkInstance &instance);
  VkSurfaceKHR getSurfaceKHR();
};
} // namespace vtt