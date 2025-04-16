#pragma once

#include "surface.hpp"
#include <vulkan/vulkan.h>

#include "device.hpp"
#include "window.hpp"
// std
#include <fstream>
#include <iostream>
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
  Surface surface;
  std::vector<VkImageView> swapChainImageViews;
  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkCommandPool commandPool;
  VkCommandBuffer commandBuffer;

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
  void createImageViews();
  void createGraphicsPipeline();
  void createRenderPass();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffer();
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

  VkShaderModule createShaderModule(const std::vector<char> &code);
  static std::vector<char> readFile(const std::string &filename) {
    std::cout << filename << std::endl;
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
      throw std::runtime_error("failed to open file!");
    }
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
  }
};
} // namespace vtt