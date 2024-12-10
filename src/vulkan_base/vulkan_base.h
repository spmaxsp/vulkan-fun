#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <vulkan/vulkan.h>


struct VulkanContext {
    VkInstance instance;   // connection to the vulkan Instance
};

VulkanContext* initVulkan();