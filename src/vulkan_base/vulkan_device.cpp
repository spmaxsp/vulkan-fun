#include "vulkan_base.h"


bool checkLayerSupport(std::vector<const char*> requiredLayers) {

    // Get list of available layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Log the available layers
    spdlog::debug("Available layers:");
    for (const auto& layer : availableLayers) {
        spdlog::debug(" - \"{0}\"", layer.layerName);
        spdlog::debug("        {0}", layer.description);
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


bool checkExtensionSupport(std::vector<const char*> requiredExtensions) {

    // Get list of available extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    // Log the available extensions
    spdlog::debug("Available extensions:");
    for (const auto& extension : availableExtensions) {
        spdlog::debug(" - \"{0}\"", extension.extensionName);
    } 

    // check if all requested extensions are available
    for (const char* requiredExtension : requiredExtensions) {
        bool extensionFound = false;
        for (const auto& extension : availableExtensions) {
            if (strcmp(requiredExtension, extension.extensionName) == 0) {
                spdlog::info("Extension \"{0}\" found", requiredExtension);
                extensionFound = true;
                break;
            }
        }
        if (!extensionFound) {
            spdlog::error("Extension \"{0}\" not found", requiredExtension);
            return false;
        }
    }
    
    return true;
}


bool selectPhysicalDevice(VulkanContext* context) {

    // Get the number of available Devices
    uint32_t numDevices = 0;
    vkEnumeratePhysicalDevices(context->instance, &numDevices, nullptr);

    // Check if devices were found
    if (numDevices == 0) {
        spdlog::error("No compatible Vulkan Devices were found");
        context->physicalDevice = nullptr;
        return false;
    }

    // Get the list of Devices
    std::vector<VkPhysicalDevice> physicalDevices(numDevices);
    vkEnumeratePhysicalDevices(context->instance, &numDevices, physicalDevices.data());

    // Log the available devices
    spdlog::debug("Available devices:");
    for (const auto& device : physicalDevices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        spdlog::debug(" - \"{0}\"", deviceProperties.deviceName);
    }

    // Select the first device
    context->physicalDevice = physicalDevices[0];
    vkGetPhysicalDeviceProperties(context->physicalDevice, &context->physicalDeviceProperties);
    spdlog::info("Selected device: \"{0}\"", context->physicalDeviceProperties.deviceName);


    return true;
}


bool initVulkanInstance(VulkanContext* context, std::vector<const char*> requiredLayers, std::vector<const char*> requiredExtensions) {

    // check layer support
    if (!checkLayerSupport(requiredLayers)) {
        spdlog::info("Layers requested, but not available!");
        return false;
    }

    // check extension support
    if (!checkExtensionSupport(requiredExtensions)) {
        spdlog::info("Extensions requested, but not available!");
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
    createInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
    createInfo.ppEnabledLayerNames = requiredLayers.data();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    // create a new Vulkan instance using the supplied information
    spdlog::info("creating Vulkan instance");
    if (vkCreateInstance(&createInfo, nullptr, &context->instance) != VK_SUCCESS) {
        spdlog::error("Error creating Vulkan instance");
        return false;
    }

    return true;
}


VulkanContext* initVulkan(std::vector<const char*> requiredLayers, std::vector<const char*> requiredExtensions) {
    VulkanContext* context = new VulkanContext;

    // create the Vulkan instance
    if (!initVulkanInstance(context, requiredLayers, requiredExtensions)) {
        return nullptr;
    }

    // create the Vulkan instance
    if (!selectPhysicalDevice(context)) {
        return nullptr;
    }

    return context;
}

void destroyVulkan(VulkanContext** context) {

    if (context == nullptr) {
        return;
    }

    if ((*context) == nullptr) {
        return;
    }

    spdlog::info("destroying Vulkan instance");
    vkDestroyInstance((*context)->instance, nullptr);

    delete (*context);
    *context = nullptr;
}
