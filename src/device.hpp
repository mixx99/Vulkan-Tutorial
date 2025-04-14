#pragma once

#include "QueueFamilyIndices.hpp"
#include <vulkan/vulkan.h>

namespace vtt {
class Device {
private:
  VkDevice device;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkQueue graphicsQueue;
  VkSurfaceKHR surface;
  VkQueue presentQueue;

public:
  void pickPhysicalDevice(const VkInstance &instance);
  bool isDeviceSuitable(const VkPhysicalDevice &device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  void createLogicalDevice();
  void setSurfaceKHR(const VkSurfaceKHR &surface_2);

public:
  VkDevice getDevice();
};
} // namespace vtt