#include "triangle.hpp"
//std
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <assert.h>
namespace vtt
{
    bool checkAllSupportedExtensions(
        const uint32_t& glfwExtensionCount, 
        const std::vector<VkExtensionProperties>& extensions,
        const char** glfwExtensions);

    void Triangle::run() 
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    void Triangle::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanTutorial", nullptr, nullptr);
    }

    void Triangle::initVulkan()
    {
        createInstance();
        pickPhysicalDevice();
    }

    void Triangle::pickPhysicalDevice()
    {
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if(deviceCount == 0)
        {
            throw std::runtime_error("Failed to find GPUs with Vulkan support");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for(const auto& device : devices)
        {
            if(isDeviceSuitable(device))
            {
                physicalDevice = device;
                break;
            }
        }
        if(physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("Failed to find suitable GPU");
    }
    bool Triangle::isDeviceSuitable(const VkPhysicalDevice& device)
    {
        QueueFamilyIndices indicies = findQueueFamilies(device);
        return indicies.graphicsFamily.has_value(); // we can also add to struct method isComplete
    }
    Triangle::QueueFamilyIndices Triangle::findQueueFamilies(VkPhysicalDevice device) 
    {
        Triangle::QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,queueFamilies.data());

        int i = 0;
        for(const auto& queueFamily : queueFamilies)
        {
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = i;
            ++i;
        }
        return indices;
    }
    void Triangle::mainLoop()
    {
        while(!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }
    void Triangle::cleanup()
    {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    bool Triangle::checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        
        for(const char* layerName : validationLayers)
        {
            bool layerFound = false;
            for(const auto& layerProperties : availableLayers)
            {
                if(strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }
            if(!layerFound)
                return false;
        }
        return true;
    }

    void Triangle::createInstance()
    {
        if (enableValidationLayers && !checkValidationLayerSupport()) 
        {
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
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if (enableValidationLayers) 
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else 
        {
            createInfo.enabledLayerCount = 0;
        }
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if(result != VK_SUCCESS)
            throw std::runtime_error("Failed To Vulkan Instance");

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        
        // Challenge from VKtutorial
        if(checkAllSupportedExtensions(glfwExtensionCount, extensions, glfwExtensions))
            std::cout << "All Extensions are good" << std::endl;
        else
            std::cerr << "Something went wrong with some Extensions.";
    }
    bool checkAllSupportedExtensions(
        const uint32_t& glfwExtensionCount, 
        const std::vector<VkExtensionProperties>& extensions,
        const char** glfwExtensions)
    {
        assert(glfwExtensions != nullptr);
        bool result = true;
        for(uint32_t i = 0; i < glfwExtensionCount; ++i)
        {
            bool found = false;
            for(const auto &extension : extensions)
            {
                if(strcmp(extension.extensionName, glfwExtensions[i]))
                    found = true;
            }
            if(!found)
            {
                std::cerr << "NOT MATCH EXTENSION: " << glfwExtensions[i] << std::endl;
                result = false;
            }
        }
        return result;
    }
} // namespace vtt