#include "function.h" 

void ImGuiInit() {
    // Font and Size of Gui SFML is bad with this
    ImGui::GetIO().FontGlobalScale = 3.f;
    ImGui::GetStyle().ScaleAllSizes(3.f);
}

void ImGuiWidgets(
        std::filesystem::__cxx11::path& lastSelectedFile, 
        char str_hold[], 
        ImGui::FileBrowser& fileDialog) {
        fileDialog.Display();
        if(fileDialog.HasSelected()) {
            // Clear the Window
            strncpy(str_hold, "", 2048); 
            std::ifstream istream;
            istream.open(fileDialog.GetSelected().string());
            if(!istream) {
                std::cout << "Opening file failed!" << std::endl;
            }
            char c;
            for(std::string line; std::getline(istream, line);) {
                strncat(str_hold, line.c_str(), line.size());
                strcat(str_hold, "\n");
            }
            istream.close();
            lastSelectedFile = fileDialog.GetSelected();
            fileDialog.ClearSelected();
        }
        // ImGui Window
        if(ImGui::BeginMenuBar()) {
            if(ImGui::BeginMenu("File")) {
                if(ImGui::MenuItem("Open")) {
                    fileDialog.Open();
                }
                if(ImGui::MenuItem("Save")) {
                    std::ofstream ostream;
                    ostream.open(lastSelectedFile.string());
                    if(!ostream) {
                        std::cout << "Opening file failed!" << std::endl;
                    }
                    ostream.write((char * )str_hold, 2048);
                    ostream.close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::InputTextMultiline("", str_hold, 2048, ImVec2(2510, 1260), 
                ImGuiInputTextFlags_AllowTabInput); 
}
