#include "surface.hpp"
#include "window.hpp"
#include <iostream>
#include <stdexcept>
namespace vtt {
void Surface::createSurface(Window &window, const VkInstance &instance) {
  VkWin32SurfaceCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.hwnd = glfwGetWin32Window(window.getWindow());
  createInfo.hinstance = GetModuleHandle(nullptr);
  if (window.getWindow() == nullptr)
    std::cout << "asdasdsa";
  if (vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface) !=
      VK_SUCCESS)
    throw std::runtime_error("Failed to create window surface!");
}
void Surface::destroySurface(const VkInstance &instance) {
  vkDestroySurfaceKHR(instance, surface, nullptr);
}
VkSurfaceKHR Surface::getSurfaceKHR() { return surface; }
} // namespace vtt