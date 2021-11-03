# GLFW DearImGui Template

Starter project for OpenGL with [DearImGui](https://github.com/ocornut/imgui) using cmake.

The template offer a starter example of a basic color picker to change the clear color of the window, as in Figure below.

![Starter Example](example.png)

`git clone https://github.com/Cryoscopic-E/GLFW-DearImGUI-Template.git <yourfolder>`

Change your project name in the _CMakeLists.txt_ in the root folder.

After cloning this template repo initiaize the submodules dependencies ([glfw](https://github.com/glfw/glfw), [glad](https://github.com/Dav1dde/glad), [glm](https://github.com/g-truc/glm))

`git submodule update --init --recursive`

To compile:

`cd <yourfolder>`

`mkdir build`

`cmake ..`

`make`
