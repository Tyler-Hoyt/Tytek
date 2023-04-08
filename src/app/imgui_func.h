#include "imgui.h"
#include "imgui-filebrowser/imfilebrowser.h"

#include <iostream>
#include <fstream>
#include <vector>

void fileDialogInit(ImGui::FileBrowser* fileDialog);
void ImGuiWidgets(ImGui::FileBrowser* fileDialog, int& height, int& width, std::string& lastSelectedFile);
