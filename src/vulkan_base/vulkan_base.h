#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <vulkan/vulkan.h>

#include <cassert>


#define ASSERT_VULKAN(x) if(x != VK_SUCCESS) {assert(false);}


struct VulkanContext {
    VkInstance instance;   // connection to the vulkan Instance
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties physicalDeviceProperties;
};

VulkanContext* initVulkan(std::vector<const char*> requiredLayers, std::vector<const char*> requiredExtensions);  
void destroyVulkan(VulkanContext** context);  