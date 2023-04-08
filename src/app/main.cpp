#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_func.h"
#include "imgui-filebrowser/imfilebrowser.h"
#include "imgui_style.h"

#include <stdio.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{

    // Setup file explorer
    ImGui::FileBrowser* fileDialog = new ImGui::FileBrowser();
    fileDialogInit(fileDialog);
    
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

#if defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(2560, 1440, "Tytek", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwSetWindowSizeLimits(window, 1000, 1000, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsLight();
    style.ScaleAllSizes(2.f);

    setImGuiStyle(style);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 3.f;
    io.WantCaptureMouse = true;

    // Setup string for saving a selected file
    std::string lastSelectedFile;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    float clear_color[] {0.5f, 0.2f, 0.30f, 1.00f};

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui Window Resize Handling
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Sample Window
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Tytek", NULL,
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoCollapse);

        ImGuiWidgets(fileDialog, height, width, lastSelectedFile);

        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui::EndFrame();
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(clear_color[0] * clear_color[3], clear_color[1] * clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete fileDialog;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
