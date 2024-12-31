# Vulkan Fun

This is a simple repository for learning and trying out stuff in Vulkan. Im mostly following the german tutorial series by Pilzschaf [Vulkan Tutorial-Pilzschaf](https://www.youtube.com/watch?v=WdbscnVj4ek&list=PLStQc0GqppuXgs6do23v_HKRrR32gJMm3).
In some cases I might deviate from the tutorial to try out some stuff on my own or implement something differently.


Im also trying documenting my progress including some notes below.  


## Progress and Notes

### 0. Vulkan Setup

- The Project requires SDL2 and the Vulkan SDK. (on arch the vulkan sdk is available in `vulkan-devel`)
- The Cmake locates both using the `find_package` command.
- As logger the spdlog library is used. It is included as a submodule in the project.
- For later the imgui library is included as a submodule as well.

### 1. Creating the SDL Window
SDL is used to Create the Window the Vulkan Application will render to.

- `SDL_MAIN_HANDLED` is defined to prevent SDL from overwriting the existing main function
- The SDL Instance is initialized (`SDL_Init()`)
- Create the SDL-Window Instance (supplying the Name, Position, Size, Flags) (`SDL_CreateWindow()`)
- Create a main loop to check for events (`SDL_PollEvent()`)
- Cleanup the SDL Instance (`SDL_DestroyWindow()` and `SDL_Quit()`)

### 2. Vulkan Instance
The Vulkan Instance represents the connection between the application and the Vulkan Library. It is the first step in creating a Vulkan Application.

- A Vulkan Instance is created using the `vkCreateInstance()` function
- Parameters for the creation are supplied via  `VkInstanceCreateInfo` and `VkApplicationInfo`
- The instance is stored in the `VulkanContext` struct
- The context can be used over the whole application to access vulkan functions


### 3. Layers and Extensions
Layers and Extensions are used to add additional functionality to the Vulkan API. 
The Layers are mostly to add debugging functionality and the Extensions are used to add platform-specific functionality.

- Layers and Extensions are queried using `vkEnumerateInstanceLayerProperties()` and `vkEnumerateInstanceExtensionProperties()`
- The available layers and extensions are printed to the console
- The `VK_LAYER_KHRONOS_validation` layer is enabled for debugging purposes
- The `VK_KHR_surface` and `VK_KHR_***_surface` extensions allow drawing to the window surface (SDL tells which one to use `SDL_Vulkan_GetInstanceExtensions()`)
- If all required extensions and layers are available is checked before creating the instance





