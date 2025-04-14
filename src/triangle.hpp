#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "device.hpp"
// std
#include <optional>
#include <vector>
namespace vtt // vulkan triangle tutorial
{
class Triangle {
public:
  void run();

private:
  GLFWwindow *window;
  VkInstance instance;
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  Device device;

  const std::vector<const char *> validationLayers = {
      "VK_LAYER_KHRONOS_validation"};
#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif
private:
  void initWindow();
  void initVulkan();
  void mainLoop();
  void cleanup();
  void createInstance();
  bool checkValidationLayerSupport();
};
} // namespace vtt