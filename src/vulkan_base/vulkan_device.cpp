#include "vulkan_base.h"


bool checkLayerSupport(std::vector<const char*> requiredLayers) {

    // Get list of available layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Log the available layers
    spdlog::info("Available layers:");
    for (const auto& layer : availableLayers) {
        spdlog::info(" - \"{0}\"", layer.layerName);
        spdlog::info("        {0}", layer.description);
    } 

    // check if all requested layers are available
    for (const char* requiredLayer : requiredLayers) {
        bool layerFound = false;
        for (const auto& layer : availableLayers) {
            if (strcmp(requiredLayer, layer.layerName) == 0) {
                spdlog::info("Layer \"{0}\" found", requiredLayer);
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            spdlog::error("Layer \"{0}\" not found", requiredLayer);
            return false;
        }
    }
    return true;

}


bool initVulkanInstance(VulkanContext* context) {

    // check layer support
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    if (!checkLayerSupport(validationLayers)) {
        spdlog::info("Validation layers requested, but not available!");
        return false;
    }

    // specify application information
    VkApplicationInfo applicationInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    applicationInfo.pApplicationName = "Vulkan Fun";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);  //0.0.1
    applicationInfo.apiVersion = VK_API_VERSION_1_0;    //  1.2.0 - specifies the vulkan version to use

    // parameters for creating the VkInstance
    VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = nullptr;

    // create a new Vulkan instance using the supplied information
    spdlog::info("creating Vulkan instance");
    if (vkCreateInstance(&createInfo, nullptr, &context->instance) != VK_SUCCESS) {
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
