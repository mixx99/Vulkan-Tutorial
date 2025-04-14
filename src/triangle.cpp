#include "triangle.hpp"
// std
#include <assert.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace vtt {
bool checkAllSupportedExtensions(
    const uint32_t &glfwExtensionCount,
    const std::vector<VkExtensionProperties> &extensions,
    const char **glfwExtensions);

void Triangle::run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

void Triangle::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanTutorial", nullptr, nullptr);
}

void Triangle::initVulkan() {
  createInstance();
  device.pickPhysicalDevice(instance);
  device.createLogicalDevice();
}

void Triangle::mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}
void Triangle::cleanup() {
  vkDestroyDevice(device.device, nullptr);
  vkDestroyInstance(instance, nullptr);
  glfwDestroyWindow(window);
  glfwTerminate();
}
bool Triangle::checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char *layerName : validationLayers) {
    bool layerFound = false;
    for (const auto &layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }
    if (!layerFound)
      return false;
  }
  return true;
}

void Triangle::createInstance() {
  if (enableValidationLayers && !checkValidationLayerSupport()) {
    throw std::runtime_error("validation layers requested, but not available!");
  }
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "VulkanTutorial";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  if (enableValidationLayers) {
    createInfo.enabledLayerCount =
        static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }
  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if (result != VK_SUCCESS)
    throw std::runtime_error("Failed To Vulkan Instance");

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                         extensions.data());

  // Challenge from VKtutorial
  if (checkAllSupportedExtensions(glfwExtensionCount, extensions,
                                  glfwExtensions))
    std::cout << "All Extensions are good" << std::endl;
  else
    std::cerr << "Something went wrong with some Extensions.";
}
bool checkAllSupportedExtensions(
    const uint32_t &glfwExtensionCount,
    const std::vector<VkExtensionProperties> &extensions,
    const char **glfwExtensions) {
  assert(glfwExtensions != nullptr);
  bool result = true;
  for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
    bool found = false;
    for (const auto &extension : extensions) {
      if (strcmp(extension.extensionName, glfwExtensions[i]) == 0)
        found = true;
    }
    if (!found) {
      std::cerr << "NOT MATCH EXTENSION: " << glfwExtensions[i] << std::endl;
      result = false;
    }
  }
  return result;
}
} // namespace vtt
