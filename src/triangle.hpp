#pragma once
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
//std
#include <vector>
#include <optional>
namespace vtt // vulkan triangle tutorial
{
class Triangle {
    public:
        void run();
    
        struct QueueFamilyIndices
        {
            std::optional<uint32_t> graphicsFamily;
        };
    private:
        GLFWwindow* window;
        VkInstance instance;
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;

        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
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
        void pickPhysicalDevice();
        bool isDeviceSuitable(const VkPhysicalDevice& device);
        Triangle::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    };
} // namespace vtt