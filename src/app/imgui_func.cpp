#include "imgui_func.h"
#include "imgui.h"
#include "imgui_stdlib.h"

void fileDialogInit(ImGui::FileBrowser* fileDialog) {
    fileDialog->SetWindowSize(1000, 1000);
    fileDialog->SetTitle("File Browser");
}

void ImGuiWidgets(ImGui::FileBrowser* fileDialog, int& height, int& width, std::string& lastSelectedFile) { 
    // String as a char array
    static std::string my_str;

    fileDialog->Display();

    // Opening a new file and saving the address for saving
    if(fileDialog->HasSelected()) {
       // First we have to clear the window so we don't have carried text
       my_str.clear();

       std::ifstream istream;
       istream.open(fileDialog->GetSelected().string());

       if(!istream) {
            std::cout << "Could not open file!" << std::endl;
       }

       for(std::string line; std::getline(istream, line);) {
            my_str.append(line);
            my_str.append("\n");
       }
        
       istream.close();
       lastSelectedFile = fileDialog->GetSelected().string();
       fileDialog->ClearSelected();
    }

    if(ImGui::BeginMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("Open")) {
                fileDialog->Open();
            }
            if(ImGui::MenuItem("Save")) {
                std::ofstream ostream;
                ostream.open(lastSelectedFile);

                if(!ostream) {
                    std::cout << "Could not open file!" << std::endl;
                    ostream.open("untitled.txt");
                }

                ostream.write(my_str.c_str(), my_str.length());
                ostream.close();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::InputTextMultiline("##My_Str", &my_str, ImVec2(width, height - 140));
}
