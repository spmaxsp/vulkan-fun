# Vulkan Fun

This is a simple repository for learning and trying out stuff in Vulkan. Im mostly following the german tutorial series by Pilzschaf [Vulkan Tutorial-Pilzschaf](https://www.youtube.com/watch?v=WdbscnVj4ek&list=PLStQc0GqppuXgs6do23v_HKRrR32gJMm3).
In some cases I might deviate from the tutorial to try out some stuff on my own or implement something differently.


Im also trying documenting my progress including some notes below.  


## Progress and Notes

### 1. Vulkan Setup

- The Project requires SDL2 and the Vulkan SDK. (on arch the vulkan sdk is available in `vulkan-devel`)
- The Cmake locates both using the `find_package` command.
- As logger the spdlog library is used. It is included as a submodule in the project.
- For later the imgui library is included as a submodule as well.

### 2. Creating the SDL Window




