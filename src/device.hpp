#pragma once

#include "QueueFamilyIndices.hpp"
#include <vector>
#include <vulkan/vulkan.h>
namespace vtt {
class Device {
private:
  VkDevice device;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkQueue graphicsQueue;
  VkSurfaceKHR surface;
  VkQueue presentQueue;
  std::vector<const char *> deviceExtensions = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };

public:
  void pickPhysicalDevice(const VkInstance &instance);
  bool isDeviceSuitable(const VkPhysicalDevice &device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  void createLogicalDevice();
  void setSurfaceKHR(const VkSurfaceKHR &surface_2);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

public:
  VkDevice getDevice();
};
} // namespace vtt