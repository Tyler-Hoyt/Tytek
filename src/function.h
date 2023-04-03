// File Dependencies
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui-filebrowser/imfilebrowser.h"

// Libraries
#include <fstream>
#include <iostream>

// Function Declarations
void ImGuiInit();
void ImGuiWidgets(
        std::filesystem::__cxx11::path& lastSelectedFile, 
        char str_hold[], 
        ImGui::FileBrowser& fileDialog);
