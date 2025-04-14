#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "device.hpp"
#include "window.hpp"
// std
#include <optional>
#include <vector>

namespace vtt // vulkan triangle tutorial
{
class Triangle {
public:
  void run();

private:
  VkInstance instance;

  Device device;
  Window window;

  const std::vector<const char *> validationLayers = {
      "VK_LAYER_KHRONOS_validation"};
#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif
private:
  void initVulkan();
  void mainLoop();
  void cleanup();
  void createInstance();
  bool checkValidationLayerSupport();
};
} // namespace vtt