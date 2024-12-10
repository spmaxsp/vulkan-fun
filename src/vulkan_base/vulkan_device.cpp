#include "vulkan_base.h"


bool initVulkanInstance(VulkanContext* context) {


    // specify application information
    VkApplicationInfo applicationInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    applicationInfo.pApplicationName = "Vulkan Fun";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);  //0.0.1
    applicationInfo.apiVersion = VK_API_VERSION_1_0;    //  1.2.0 - specifies the vulkan version to use

    // parameters for creating the VkInstance
    VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = 0;
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = 0;

    // create a new Vulkan instance using the supplied information
    spdlog::info("creating Vulkan instance");
    if (vkCreateInstance(&createInfo, 0, &context->instance) != VK_SUCCESS) {
        spdlog::error("Error creating Vulkan instance");
        return false;
    }

    return true;
}


VulkanContext* initVulkan() {
    VulkanContext* context = new VulkanContext;

    // create the Vulkan instance
    if (initVulkanInstance(context)) {
        return 0;
    }

    return context;
}
